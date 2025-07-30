#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "AquaGardian";
const char* password = "onetoeight";

// Motor control pins
byte F = 15;
byte B = 2;
byte L = 16;
byte R = 17;
byte S = 5;

int step_time = 100;
AsyncWebServer server(80);


// Embedded HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>  // Initialize motor pins
  pinMode(R_leg_F, OUTPUT);
  pinMode(R_leg_B, OUTPUT);
  pinMode(L_leg_F, OUTPUT);
  pinMode(L_leg_B, OUTPUT);

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Robot Controller</title>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@300;400;500;600;700;800&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        :root {
            /* Light Mode Defaults */
            --primary: #4361ee;
            --primary-light: #4895ef;
            --primary-dark: #3f37c9;
            --secondary: #7209b7;
            --accent: #f72585;
            --success: #4cc9f0;
            --warning: #f8961e;
            --danger: #ef233c;
            --text: #2b2d42;
            --text-light: #8d99ae;
            --bg: #f8f9fa;
            --bg-gradient: linear-gradient(135deg, #f5f7fa 0%, #e4e8f0 100%);
            --panel: #ffffff;
            --panel-hover: #f1f3f8;
            --border: rgba(0, 0, 0, 0.1);
            --shadow: 0 4px 20px rgba(0, 0, 0, 0.08);
            --shadow-hover: 0 8px 30px rgba(0, 0, 0, 0.12);
            --glow: 0 0 15px rgba(67, 97, 238, 0.3);
            
            /* Dark Mode Overrides */
            --dark-primary: #5e60ce;
            --dark-primary-light: #64dfdf;
            --dark-primary-dark: #5390d9;
            --dark-secondary: #b5179e;
            --dark-accent: #f72585;
            --dark-success: #52b788;
            --dark-warning: #f8961e;
            --dark-danger: #ef233c;
            --dark-text: #edf2f4;
            --dark-text-light: #adb5bd;
            --dark-bg: #121212;
            --dark-bg-gradient: linear-gradient(135deg, #1a1a1a 0%, #0d0d0d 100%);
            --dark-panel: #1e1e1e;
            --dark-panel-hover: #2a2a2a;
            --dark-border: rgba(255, 255, 255, 0.1);
            --dark-shadow: 0 4px 20px rgba(0, 0, 0, 0.3);
            --dark-shadow-hover: 0 8px 30px rgba(0, 0, 0, 0.4);
            --dark-glow: 0 0 20px rgba(100, 223, 223, 0.4);

            /* Responsive sizes */
            --base-size: 1rem;
            --scale: 1.25;
            --h1: calc(var(--h2) * var(--scale));
            --h2: calc(var(--h3) * var(--scale));
            --h3: calc(var(--h4) * var(--scale));
            --h4: calc(var(--h5) * var(--scale));
            --h5: calc(var(--base-size) * var(--scale));
            --small: calc(var(--base-size) / var(--scale));

            /* Animation */
            --transition: all 0.3s cubic-bezier(0.25, 0.8, 0.25, 1);
            --transition-fast: all 0.15s ease;
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Montserrat', sans-serif;
            background: var(--bg-gradient);
            color: var(--text);
            line-height: 1.6;
            min-height: 100vh;
            transition: var(--transition);
            font-size: var(--base-size);
        }

        body.dark-mode {
            --primary: var(--dark-primary);
            --primary-light: var(--dark-primary-light);
            --primary-dark: var(--dark-primary-dark);
            --secondary: var(--dark-secondary);
            --accent: var(--dark-accent);
            --success: var(--dark-success);
            --warning: var(--dark-warning);
            --danger: var(--dark-danger);
            --text: var(--dark-text);
            --text-light: var(--dark-text-light);
            --bg: var(--dark-bg);
            --bg-gradient: var(--dark-bg-gradient);
            --panel: var(--dark-panel);
            --panel-hover: var(--dark-panel-hover);
            --border: var(--dark-border);
            --shadow: var(--dark-shadow);
            --shadow-hover: var(--dark-shadow-hover);
            --glow: var(--dark-glow);
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 2rem 1.5rem;
        }

        h1 { font-size: var(--h1); font-weight: 800; }
        h2 { font-size: var(--h2); font-weight: 700; }
        h3 { font-size: var(--h3); font-weight: 600; }
        h4 { font-size: var(--h4); font-weight: 500; }
        h5 { font-size: var(--h5); font-weight: 500; }
        small { font-size: var(--small); color: var(--text-light); }

        /* Header */
        header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 2.5rem;
            padding-bottom: 1.5rem;
            border-bottom: 1px solid var(--border);
            position: relative;
        }

        .header-content {
            display: flex;
            align-items: center;
            gap: 1rem;
        }

        .logo {
            width: 50px;
            height: 50px;
            background: var(--primary);
            border-radius: 12px;
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 1.5rem;
            box-shadow: var(--shadow);
        }

        h1 {
            color: var(--text);
            background: linear-gradient(90deg, var(--primary), var(--primary-light));
            -webkit-background-clip: text;
            background-clip: text;
            -webkit-text-fill-color: transparent;
            display: inline-block;
        }

        .header-actions {
            display: flex;
            align-items: center;
            gap: 1rem;
        }

        /* Theme Toggle */
        .theme-toggle {
            position: relative;
            width: 50px;
            height: 26px;
            border-radius: 50px;
            background: var(--panel);
            border: 1px solid var(--border);
            cursor: pointer;
            box-shadow: var(--shadow);
            transition: var(--transition);
        }

        .theme-toggle:hover {
            box-shadow: var(--shadow-hover);
        }

        .theme-toggle::before {
            content: '';
            position: absolute;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: var(--primary);
            top: 2px;
            left: 2px;
            transition: transform 0.3s ease;
        }

        body.dark-mode .theme-toggle::before {
            transform: translateX(24px);
            background: var(--primary-light);
        }

        .theme-toggle i {
            position: absolute;
            font-size: 0.8rem;
            color: white;
        }

        .theme-toggle i.fa-sun {
            left: 6px;
            top: 5px;
        }

        .theme-toggle i.fa-moon {
            right: 6px;
            top: 5px;
        }

        /* Connection Status */
        .connection-status {
            display: flex;
            align-items: center;
            gap: 0.75rem;
            font-weight: 500;
            padding: 0.5rem 1rem;
            background: var(--panel);
            border-radius: 50px;
            box-shadow: var(--shadow);
            transition: var(--transition);
        }

        .connection-status:hover {
            box-shadow: var(--shadow-hover);
        }

        #status-indicator {
            width: 12px;
            height: 12px;
            border-radius: 50%;
            background-color: var(--danger);
            position: relative;
        }

        #status-indicator::after {
            content: '';
            position: absolute;
            width: 100%;
            height: 100%;
            border-radius: 50%;
            background-color: inherit;
            opacity: 0.6;
            animation: pulse 1.5s infinite;
        }

        @keyframes pulse {
            0% { transform: scale(1); opacity: 0.6; }
            70% { transform: scale(2.5); opacity: 0; }
            100% { transform: scale(1); opacity: 0; }
        }

        .connected #status-indicator {
            background-color: var(--success);
        }

        .connected #status-indicator::after {
            animation: none;
        }

        /* Control Panel */
        .control-panel {
            background: var(--panel);
            border-radius: 20px;
            padding: 2rem;
            box-shadow: var(--shadow);
            margin-bottom: 2rem;
            transition: var(--transition);
        }

        .control-panel:hover {
            box-shadow: var(--shadow-hover);
        }

        .panel-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 1.5rem;
        }

        h2 {
            color: var(--text);
            position: relative;
            display: inline-block;
        }

        h2::after {
            content: '';
            position: absolute;
            bottom: -5px;
            left: 0;
            width: 50px;
            height: 3px;
            background: linear-gradient(90deg, var(--primary), var(--primary-light));
            border-radius: 3px;
        }

        /* Direction Pad */
        .direction-pad-container {
            display: flex;
            justify-content: center;
            margin-bottom: 2rem;
        }

        .direction-pad {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            grid-template-rows: repeat(3, 1fr);
            gap: 1rem;
            max-width: 400px;
            width: 100%;
        }

        .control-btn {
            border: none;
            border-radius: 16px;
            background: var(--panel);
            color: var(--text);
            font-size: 1.75rem;
            cursor: pointer;
            box-shadow: var(--shadow);
            aspect-ratio: 1;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: var(--transition);
            position: relative;
            overflow: hidden;
        }

        .control-btn::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background: linear-gradient(135deg, rgba(255,255,255,0.2) 0%, rgba(255,255,255,0) 100%);
            opacity: 0;
            transition: var(--transition);
        }

        .control-btn:hover {
            transform: translateY(-5px);
            box-shadow: var(--shadow-hover);
        }

        .control-btn:hover::before {
            opacity: 1;
        }

        .control-btn:active {
            transform: translateY(0);
            filter: brightness(0.95);
        }

        /* Color-Coded Buttons */
        .forward { 
            background: linear-gradient(135deg, var(--success) 0%, #38b000 100%);
            color: white;
            grid-column: 2;
            grid-row: 1;
        }

        .backward { 
            background: linear-gradient(135deg, var(--danger) 0%, #d00000 100%);
            color: white;
            grid-column: 2;
            grid-row: 3;
        }

        .left { 
            background: linear-gradient(135deg, var(--primary-light) 0%, var(--primary-dark) 100%);
            color: white;
            grid-column: 1;
            grid-row: 2;
        }

        .right { 
            background: linear-gradient(135deg, var(--primary-light) 0%, var(--primary-dark) 100%);
            color: white;
            grid-column: 3;
            grid-row: 2;
        }

        .stop { 
            background: linear-gradient(135deg, var(--warning) 0%, #f3722c 100%);
            color: white;
            grid-column: 2;
            grid-row: 2;
        }

        /* Speed Control */
        .speed-control {
            background: var(--panel);
            padding: 1.5rem;
            border-radius: 16px;
            box-shadow: var(--shadow);
            margin-bottom: 2rem;
            transition: var(--transition);
        }

        .speed-control:hover {
            box-shadow: var(--shadow-hover);
        }

        .speed-control label {
            display: block;
            margin-bottom: 1rem;
            font-weight: 600;
            color: var(--text);
        }

        .speed-slider {
            -webkit-appearance: none;
            width: 100%;
            height: 10px;
            border-radius: 5px;
            background: linear-gradient(90deg, var(--primary), var(--primary-light));
            outline: none;
            transition: var(--transition);
        }

        .speed-slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.2);
            border: 3px solid var(--primary);
            transition: var(--transition);
        }

        .speed-slider::-moz-range-thumb {
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.2);
            border: 3px solid var(--primary);
            transition: var(--transition);
        }

        .speed-value {
            display: flex;
            justify-content: space-between;
            margin-top: 0.5rem;
            font-size: 0.9rem;
            color: var(--text-light);
        }

        /* Feature Buttons */
        .additional-features {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 1.5rem;
            margin-top: 2rem;
        }

        .feature-btn {
            padding: 1.25rem;
            border: none;
            border-radius: 16px;
            background: var(--panel);
            color: var(--text);
            font-size: 1rem;
            font-weight: 500;
            cursor: pointer;
            box-shadow: var(--shadow);
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 0.75rem;
            transition: var(--transition);
            position: relative;
            overflow: hidden;
        }

        .feature-btn::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background: linear-gradient(135deg, rgba(255,255,255,0.2) 0%, rgba(255,255,255,0) 100%);
            opacity: 0;
            transition: var(--transition);
        }

        .feature-btn:hover {
            transform: translateY(-3px);
            box-shadow: var(--shadow-hover);
        }

        .feature-btn:hover::before {
            opacity: 1;
        }

        .feature-btn:active {
            transform: translateY(0);
            filter: brightness(0.95);
        }

        #led-toggle {
            background: linear-gradient(135deg, var(--primary) 0%, var(--primary-light) 100%);
            color: white;
        }

        #horn {
            background: linear-gradient(135deg, var(--secondary) 0%, #b5179e 100%);
            color: white;
        }

        #emergency-stop {
            background: linear-gradient(135deg, var(--danger) 0%, #d00000 100%);
            color: white;
            animation: pulse-glow 2s infinite;
        }

        @keyframes pulse-glow {
            0% { box-shadow: 0 0 0 0 rgba(239, 35, 60, 0.4); }
            70% { box-shadow: 0 0 0 15px rgba(239, 35, 60, 0); }
            100% { box-shadow: 0 0 0 0 rgba(239, 35, 60, 0); }
        }

        /* Battery Indicator */
        .battery-indicator {
            background: var(--panel);
            padding: 1.5rem;
            border-radius: 16px;
            box-shadow: var(--shadow);
            margin-top: 2rem;
            transition: var(--transition);
        }

        .battery-indicator:hover {
            box-shadow: var(--shadow-hover);
        }

        .battery-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 1rem;
        }

        .battery-icon {
            font-size: 1.5rem;
            color: var(--success);
        }

        .battery-level {
            height: 20px;
            background: var(--bg);
            border-radius: 10px;
            overflow: hidden;
            position: relative;
        }

        .battery-fill {
            height: 100%;
            width: 75%;
            background: linear-gradient(90deg, var(--success) 0%, #38b000 100%);
            border-radius: 10px;
            transition: width 0.5s ease;
        }

        .battery-percentage {
            position: absolute;
            right: 10px;
            top: 50%;
            transform: translateY(-50%);
            font-size: 0.8rem;
            font-weight: 600;
            color: white;
            text-shadow: 0 1px 2px rgba(0, 0, 0, 0.3);
        }

        /* Responsive */
        @media (max-width: 768px) {
            .container {
                padding: 1.5rem 1rem;
            }
            
            header {
                flex-direction: column;
                align-items: flex-start;
                gap: 1rem;
            }
            
            .header-actions {
                width: 100%;
                justify-content: space-between;
            }
            
            .direction-pad {
                max-width: 300px;
            }
            
            .additional-features {
                grid-template-columns: 1fr;
            }
        }

        @media (max-width: 480px) {
            .direction-pad {
                gap: 0.75rem;
            }
            
            .control-btn {
                font-size: 1.5rem;
            }
            
            .feature-btn {
                padding: 1rem;
                font-size: 0.9rem;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <div class="header-content">
                <div class="logo">
                    <i class="fas fa-robot"></i>
                </div>
                <h1>ESP32 Robot Controller</h1>
            </div>
            <div class="header-actions">
                <div class="connection-status" id="connection-status">
                    <span id="status-indicator"></span>
                    <span id="status-text">HTTP Mode</span>
                </div>
                <div class="theme-toggle" id="theme-toggle">
                    <i class="fas fa-sun"></i>
                    <i class="fas fa-moon"></i>
                </div>
            </div>
        </header>

        <div class="control-panel">
            <div class="panel-header">
                <h2><i class="fas fa-gamepad"></i> Direction Control</h2>
                <small>Tap or click to control movement</small>
            </div>
            
            <div class="direction-pad-container">
                <div class="direction-pad">
                    <a href="/F" class="control-btn forward" id="F"><i class="fas fa-arrow-up"></i></a>
                    <a href="/L" class="control-btn left" id="L"><i class="fas fa-arrow-left"></i></a>
                    <a href="/S" class="control-btn stop" id="S"><i class="fas fa-stop"></i></a>
                    <a href="/R" class="control-btn right" id="R"><i class="fas fa-arrow-right"></i></a>
                    <a href="/B" class="control-btn backward" id="B"><i class="fas fa-arrow-down"></i></a>
                </div>
            </div>

            <div class="speed-control">
                <label for="speed-slider"><i class="fas fa-tachometer-alt"></i> Speed Control</label>
                <input type="range" min="0" max="100" value="50" class="speed-slider" id="speed-slider">
                <div class="speed-value">
                    <span>Slow</span>
                    <span>Medium</span>
                    <span>Fast</span>
                </div>
            </div>

            <div class="panel-header">
                <h2><i class="fas fa-cogs"></i> Additional Features</h2>
                <small>Accessories and emergency functions</small>
            </div>

            <div class="additional-features">
                <a href="/led" class="feature-btn" id="led-toggle"><i class="fas fa-lightbulb"></i> Toggle LED</a>
                <a href="/H" class="feature-btn" id="horn"><i class="fas fa-bell"></i> Horn</a>
                <a href="/S" class="feature-btn" id="emergency-stop"><i class="fas fa-exclamation-triangle"></i> Emergency Stop</a>
            </div>
        </div>

        <div class="battery-indicator">
            <div class="battery-header">
                <h3><i class="fas fa-battery-three-quarters"></i> Battery Status</h3>
                <i class="fas fa-bolt battery-icon"></i>
            </div>
            <div class="battery-level">
                <div class="battery-fill" id="battery-fill"></div>
                <span class="battery-percentage" id="battery-percentage">75%</span>
            </div>
        </div>
    </div>

    <script>
        // Theme Toggle
        const themeToggle = document.getElementById('theme-toggle');
        const body = document.body;
        
        // Check for saved theme preference or use preferred color scheme
        const savedTheme = localStorage.getItem('theme') || 
                         (window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light');
        
        if (savedTheme === 'dark') {
            body.classList.add('dark-mode');
        }
        
        themeToggle.addEventListener('click', () => {
            body.classList.toggle('dark-mode');
            const theme = body.classList.contains('dark-mode') ? 'dark' : 'light';
            localStorage.setItem('theme', theme);
        });
        
        // Simulate connection status (replace with actual connection logic)
        const connectionStatus = document.getElementById('connection-status');
        const statusIndicator = document.getElementById('status-indicator');
        const statusText = document.getElementById('status-text');
        
        setTimeout(() => {
            connectionStatus.classList.add('connected');
            statusText.textContent = 'Connected';
            
            // Simulate battery level updates
            let batteryLevel = 75;
            const batteryFill = document.getElementById('battery-fill');
            const batteryPercentage = document.getElementById('battery-percentage');
            
            const batteryInterval = setInterval(() => {
                batteryLevel -= 1;
                if (batteryLevel <= 20) {
                    batteryFill.style.background = 'linear-gradient(90deg, var(--warning) 0%, #f3722c 100%)';
                }
                if (batteryLevel <= 10) {
                    batteryFill.style.background = 'linear-gradient(90deg, var(--danger) 0%, #d00000 100%)';
                }
                if (batteryLevel <= 0) {
                    batteryLevel = 100;
                    batteryFill.style.background = 'linear-gradient(90deg, var(--success) 0%, #38b000 100%)';
                }
                batteryFill.style.width = `${batteryLevel}%`;
                batteryPercentage.textContent = `${batteryLevel}%`;
            }, 10000);
        }, 2000);
        
        // Button press animations
        const buttons = document.querySelectorAll('.control-btn, .feature-btn');
        buttons.forEach(button => {
            button.addEventListener('mousedown', () => {
                button.style.transform = 'translateY(2px)';
                button.style.filter = 'brightness(0.9)';
            });
            
            button.addEventListener('mouseup', () => {
                button.style.transform = '';
                button.style.filter = '';
            });
            
            button.addEventListener('mouseleave', () => {
                button.style.transform = '';
                button.style.filter = '';
            });
            
            // For touch devices
            button.addEventListener('touchstart', () => {
                button.style.transform = 'translateY(2px)';
                button.style.filter = 'brightness(0.9)';
            });
            
            button.addEventListener('touchend', () => {
                button.style.transform = '';
                button.style.filter = '';
            });
        });
        
        // Speed control (simulated - you would send this to your ESP32)
        const speedSlider = document.getElementById('speed-slider');
        speedSlider.addEventListener('input', () => {
            // Here you would send the speed value to your ESP32
            console.log(`Speed set to: ${speedSlider.value}%`);
        });
    </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(F,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(L,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(S,OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/F", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(F);
    request->send_P(200, "text/html", index_html);
  });

  server.on("/B", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(B);
    request->send_P(200, "text/html", index_html);
  });

  server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(L);
    request->send_P(200, "text/html", index_html);
  });

  server.on("/R", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(R);
    request->send_P(200, "text/html", index_html);
  });

  server.on("/S", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(S);
    request->send_P(200, "text/html", index_html);
  });

  server.begin();
}

void loop() {

}
