# -IoT-Integrated-Medicine-Vending-System

## Overview
This project is an innovative IoT-based solution for dispensing prescription medications, providing a contactless, automated system for doctors, patients, and pharmacy integration. The system includes web interfaces for both doctors and patients, enabling real-time tracking and management of medical prescriptions, payments, and RFID tag-based identification for dispensing medication.

The hardware component includes an ESP32 board connected to an RFID module, which communicates with a Flask server. Patients can use RFID tags to identify themselves, view prescriptions, and make payments through Razorpay. The doctor can manage patient details and prescriptions via a web interface.

## Key Features
- **Patient Module**:
  - RFID tag scanning for patient identification.
  - View and retrieve prescription details based on the RFID tag.
  - Online payment integration using Razorpay for purchasing medications.
  - Communicates with an ESP32 microcontroller for IoT-based medication dispensing.

- **Doctor Module**:
  - Web interface to manage patient details and prescriptions.
  - Retrieve and update prescription details in real-time from Firebase.

- **IoT Hardware Integration**:
  - RFID scanner connected to an ESP32 microcontroller.
  - Sends data from the RFID module to the Flask server via HTTP requests.
  - Handles real-time data communication between hardware and the web app.

## Technologies Used
- **Backend**: Flask, Firebase, Razorpay API
- **Frontend**: HTML, CSS, JavaScript
- **Database**: Firebase Realtime Database
- **IoT Hardware**: ESP32, MFRC522 RFID module
- **Libraries/Frameworks**:
  - **Firebase Admin SDK**: For managing the database.
  - **Razorpay SDK**: For payment integration.
  - **ArduinoJSON**: For JSON parsing on ESP32.
  - **WiFi.h**: For enabling Wi-Fi communication on ESP32.
  - **HTTPClient.h**: For handling HTTP requests in ESP32.

## Software Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/IoT-Medicine-Vending-System.git
   cd IoT-Medicine-Vending-System
   ```

2.### Installation

   **Clone the repository**:

   First, download the project by cloning the repository to your local machine:

   ```bash
   git clone https://github.com/Afrinaf/IoT-Integrated-Medicine-Vending-System.git
   ```

   **Navigate to the project directory**:

   Change your directory to the project's folder:

   ```bash
   cd IoT-Integrated-Medicine-Vending-System
   ```

   **Set up the Python virtual environment**:

   It's recommended to use a virtual environment to manage dependencies.

   - **For Windows**:
     Open your terminal (Command Prompt or Git Bash) and run the following command to create a virtual environment:

     ```bash
     python -m venv myenv
     ```

     Then, activate the virtual environment:

     ```bash
     myenv\Scripts\activate
     ```

     **For Linux/Mac**:
     Run the following command to create a virtual environment:

     ```bash
     python3 -m venv myenv
     ```

     Then, activate the virtual environment:

     ```bash
     source myenv/bin/activate
     ```

   **Install the required dependencies**:

   With the virtual environment activated, install the project dependencies listed in the `requirements.txt` file:

   ```bash
   pip install -r requirements.txt
   ```

   **Set up the necessary configurations**:

   Add your API keys (e.g., Firebase) and other sensitive information to `key.json` (this file should be excluded from Git via `.gitignore`).

   **Run the application**:

   Start the Flask server by running:
   ## Patient Module
   ```bash
   python patient.py 
   ```
   ## Doctor Module
   ```bash
   python doctor.py 
   ```
  **Access the application**:

   Once the server is running, you can access the application in your web browser at:
   ## Patient Module
   ```
   http://localhost:5000
   ```
   ## Doctor Module
   ```
   http://localhost:5002
   ```

3 Configure Firebase:
   - Add your Firebase credentials in a `key.json` file and place it in the root directory.
   - Modify the `databaseURL` in the Python script to match your Firebase project.

5. Access the web interface:
   - Patient: `http://127.0.0.1:5000`
   - Doctor: `http://127.0.0.1:5002`

### Doctor Module
- The doctor uses a similar Flask setup, where they can search for patients by their RFID tag number and view prescription details.
  
### Razorpay Payment Integration
To enable payments, update the Razorpay credentials in the code:
```python
razorpay_client = razorpay.Client(auth=('YOUR_RAZORPAY_KEY', 'YOUR_RAZORPAY_SECRET'))
```

## Hardware Setup

### Components:
- **ESP32**
- **MFRC522 RFID Reader**
- **Wi-Fi Enabled (SSID: Galaxy A53 5G1A11, Password: elitepro)**
  
### Code:
1. Install necessary libraries in your Arduino IDE:
   - `MFRC522`
   - `ArduinoJson`
   - `WiFi`
   - `HTTPClient`

2. Flash the provided Arduino code to your ESP32.

3. The ESP32 will scan the RFID tag and send the tag number to the Flask server at the `/update_tag` endpoint. The server will handle this data and associate it with patient details in Firebase.

4. Hardware logic includes:
   - Detecting a new RFID tag.
   - Sending an HTTP POST request to the server with the scanned tag number.

## Screenshots
## Doctor Module
![Screenshot (323)](https://github.com/user-attachments/assets/921aab2e-dbee-4aaa-acd9-aa34142468a4)
![Screenshot (324)](https://github.com/user-attachments/assets/adb78f3d-2395-45bc-87a0-79a786060450)


## Patient Module
![Screenshot (319)](https://github.com/user-attachments/assets/b255672b-7d25-46f5-ad72-83e02c122d08)
![Screenshot_15-10-2024_173812_127 0 0 1](https://github.com/user-attachments/assets/ec923b68-e820-4d16-828f-be5636c2c5b9)
![Screenshot (321)](https://github.com/user-attachments/assets/9480e680-5edf-42e8-9fa2-053be0d9b75e)
![Screenshot (320)](https://github.com/user-attachments/assets/d59c277d-29a6-4ea6-af91-a0aa85d00d39)



## Future Enhancements
- **Automated Medicine Dispensing**: Integrate a mechanical dispenser to automatically dispense the medicine after payment.
- **Push Notifications**: Implement push notifications for patients when their prescription is ready for pickup.
- **Detailed Doctor Dashboard**: Provide real-time analytics and detailed patient history on the doctor’s dashboard.
  

## License
This project is licensed under the MIT License.
