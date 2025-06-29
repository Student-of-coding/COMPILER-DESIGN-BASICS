#include <windows.h>
#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <iomanip>

// Anonymous namespace to encapsulate parser helper functions and variables
namespace {
    const std::string* input; // Pointer to the expression string being parsed
    size_t pos;                // Current position within the input string

    // Skip over any whitespace characters
    void skipWhitespace() {
        while (pos < input->length() && std::isspace(static_cast<unsigned char>((*input)[pos])))
            pos++;
    }

    // Try to match and consume an expected character (ignoring whitespace)
    bool match(char expected) {
        skipWhitespace();
        if (pos < input->length() && (*input)[pos] == expected) {
            pos++;
            return true;
        }
        return false;
    }

    // Forward declarations for recursive parsing
    double parseExpression();
    double parseTerm();
    double parseFactor();

    // Parse a numeric literal, handling optional sign and decimal point
    double parseNumber() {
        skipWhitespace();
        size_t start = pos;
        bool hasDecimal = false;
        
        // Allow leading '+' or '-' sign
        if (match('+')) { }
        else if (match('-')) { }
        
        // Check for a leading decimal point
        if (pos < input->length() && (*input)[pos] == '.') {
            hasDecimal = true;
            pos++;
        }
        
        // Consume digits and at most one decimal point
        while (pos < input->length()) {
            if (std::isdigit(static_cast<unsigned char>((*input)[pos]))) {
                pos++;
            }
            else if ((*input)[pos] == '.' && !hasDecimal) {
                hasDecimal = true;
                pos++;
            }
            else {
                break;
            }
        }
        
        // Ensure we've consumed something
        if (start == pos) throw std::runtime_error("Expected number");
        if (pos - start == 1 && (*input)[start] == '.') 
            throw std::runtime_error("Invalid number format");
        
        // Convert substring to double
        try {
            return std::stod(input->substr(start, pos - start));
        }
        catch (...) {
            throw std::runtime_error("Invalid number format");
        }
    }

    // Parse factors: numbers, parenthesized expressions, or unary +/-
    double parseFactor() {
        skipWhitespace();
        if (match('-')) return -parseFactor(); // Unary minus
        if (match('+')) return parseFactor();  // Unary plus
        
        if (match('(')) {
            double val = parseExpression();
            if (!match(')')) throw std::runtime_error("Missing ')'");
            return val;
        }
        return parseNumber();
    }

    // Parse terms: factors combined by '*' or '/'
    double parseTerm() {
        double lhs = parseFactor();
        while (true) {
            if (match('*')) {
                lhs *= parseFactor();
            }
            else if (match('/')) {
                double rhs = parseFactor();
                if (rhs == 0) throw std::runtime_error("Division by zero");
                lhs /= rhs;
            }
            else break;
        }
        return lhs;
    }

    // Parse full expressions: terms combined by '+' or '-'
    double parseExpression() {
        double lhs = parseTerm();
        while (true) {
            if (match('+')) lhs += parseTerm();
            else if (match('-')) lhs -= parseTerm();
            else break;
        }
        return lhs;
    }
}

// Evaluate the expression string and return the numerical result
double evaluateExpression(const std::string& expr) {
    input = &expr;
    pos = 0;
    double result = parseExpression();
    skipWhitespace();
    if (pos != expr.length()) {
        // Report extra unexpected characters
        std::string msg = "Unexpected character at position " + std::to_string(pos) + ": '";
        msg += (pos < expr.length()) ? std::string(1, expr[pos]) : "end";
        msg += "'";
        throw std::runtime_error(msg);
    }
    return result;
}

// Format result to string, trimming trailing zeros
std::string formatResult(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(10) << value;
    std::string s = oss.str();
    
    // Remove unnecessary zeros and possible trailing decimal point
    size_t dot = s.find('.');
    if (dot != std::string::npos) {
        size_t last = s.find_last_not_of('0');
        if (last != std::string::npos && last >= dot) {
            s.erase(last + 1);
            if (s.back() == '.') s.pop_back();
        }
    }
    return s;
}

// Global identifiers for window class and controls
const char g_szClassName[] = "SimpleCalcClass";
HWND hInput, hButton, hResult;

// Main window procedure to handle messages/events
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            // Handle button click event
            if ((HWND)lParam == hButton && HIWORD(wParam) == BN_CLICKED) {
                int len = GetWindowTextLength(hInput);
                if (len > 0) {
                    std::string expr(len, '\0');
                    // Retrieve input text
                    GetWindowText(hInput, &expr[0], len + 1);
                    try {
                        double res = evaluateExpression(expr);  // Evaluate
                        std::string out = "Result: " + formatResult(res);
                        SetWindowText(hResult, out.c_str());    // Display result
                    }
                    catch (std::exception& e) {
                        // Show error message box
                        MessageBox(hwnd, e.what(), "Error", MB_OK | MB_ICONERROR);
                    }
                }
                else {
                    // Clear result if no input
                    SetWindowText(hResult, "Result: ");
                }
            }
            break;
            
        case WM_CREATE:
            // Create input edit control
            hInput = CreateWindow("EDIT", "",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                20, 20, 300, 30, hwnd, nullptr, nullptr, nullptr);
            // Create "Evaluate" button
            hButton = CreateWindow("BUTTON", "Evaluate",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                330, 20, 100, 30, hwnd, (HMENU)1, nullptr, nullptr);
            // Create static control to show the result
            hResult = CreateWindow("STATIC", "Result: ",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                20, 60, 410, 30, hwnd, nullptr, nullptr, nullptr);
            break;
            
        case WM_CLOSE:
            DestroyWindow(hwnd); // Clean up window
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);  // Signal end of application
            break;
            
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Application entry point (WinMain)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;
    
    // Register window class
    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create main application window
    HWND hwnd = CreateWindowEx(
        0,
        g_szClassName,
        "Arithmetic Expression Evaluator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 460, 150,
        nullptr, nullptr, hInstance, nullptr);
        
    if (!hwnd) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Display and update window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}
