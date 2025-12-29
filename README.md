# Nimons Hospital Management System (NHMS)

🏥 **Nimons Hospital Management System** is a structured and efficient hospital management application designed to handle patient registration, doctor assignments, medical diagnoses, and drug inventory management for the Nimon community.

## 📋 Table of Contents
- [Nimons Hospital Management System (NHMS)](#nimons-hospital-management-system-nhms)
  - [📋 Table of Contents](#-table-of-contents)
  - [📖 Background](#-background)
  - [🚀 Key Features](#-key-features)
    - [1. User Management](#1-user-management)
    - [2. Hospital Operations](#2-hospital-operations)
    - [3. Patient Journey](#3-patient-journey)
  - [💻 System Requirements](#-system-requirements)
  - [🛠 Installation and Build](#-installation-and-build)
  - [🏃 How to Run](#-how-to-run)
  - [⌨️ Available Commands](#️-available-commands)
  - [📂 Project Structure](#-project-structure)
  - [👥 Contributors (Group K01-E)](#-contributors-group-k01-e)

## 📖 Background
Since Gru joined the Anti-Villain League, his life has changed drastically. Alongside his wife, Lucy, he now faces the challenge of maintaining order among hundreds of Nimons—loyal but accident-prone small creatures. Dr. Nefario realized the need for a proper healthcare system to manage constant minor medical incidents. NHMS was developed to replace ineffective manual processes with a functional, safe, and orderly digital management system.

## 🚀 Key Features
The system implements various features categorized by user roles (Manager, Doctor, Patient):

### 1. User Management
* **Role-Based Access Control:** Distinct permissions for Manager, Doctor, and Patient.
* **Authentication:** Secure Login, Registration, and Logout.
* **Security:** Password reset feature using Run-Length Encoding (RLE) for unique verification codes.

### 2. Hospital Operations
* **Dynamic Map:** Visualization of the hospital layout and room statuses.
* **Room Management:** Doctor assignments and patient queue tracking per room.
* **Medical Services:** Automated diagnosis based on health parameters (blood pressure, temperature, etc.) and prescription management.

### 3. Patient Journey
* **Check-up Workflow:** Registration for check-ups, queue monitoring, medication tracking, and discharge verification.

## 💻 System Requirements
* **Operating System:** Windows, Linux, or macOS.
* **Compiler:** GCC (GNU Compiler Collection).
* **Build Tool:** Make.

## 🛠 Installation and Build
1.  Clone or extract the project folder.
2.  Navigate to the `src` directory:
    ```bash
    cd if1210-tubes-2025-k01-e/src
    ```
3.  Build the project using the provided Makefile:
    ```bash
    make all
    ```
    This will compile the source code and generate the `main` executable in the `build` directory.

## 🏃 How to Run
Run the executable from the root or `src` directory by providing the data folder name as an argument:
```bash
./build/main <folder_name>
```
Example: `./build/main demo` (loads data from `src/data/demo/`).

## ⌨️ Available Commands
| Command | Access | Description |
| :--- | :--- | :--- |
| LOGIN | All | Access the system. |
| REGISTER | All | Create a new Patient account. |
| HELP | All | Show available features for the current role. |
| LIHAT_DENAH | All | Display the 2D hospital map. |
| LIHAT_USER | Manager | List all registered users. |
| TAMBAH_DOKTER | Manager | Register a new doctor into the system. |
| ASSIGN_DOKTER | Manager | Assign a doctor to a specific room. |
| DIAGNOSIS | Doctor | Diagnose the next patient in the queue. |
| NGOBATIN | Doctor | Prescribe medicine based on diagnosis. |
| DAFTAR_CHECKUP | Patient | Register for a medical examination. |
| ANTRIAN | Patient | Check current queue position. |
| MINUM_OBAT | Patient | Consume prescribed medication. |
| PULANGDOK | Patient | Request discharge after completing treatment. |
| SAVE | All | Save current session data to files. |
| EXIT | All | Close the program. |

## 📂 Project Structure
- `src/`: Contains main source code (`.c`) and logic.
- `src/header/`: Header files (`.h`) and ADT definitions.

- `src/data/`: External data files (CSV/TXT) for users, diseases, and medicines.
- `build/`: Compiled object files and executables.
- `doc/`: Full project report and documentation.

## 👥 Contributors (Group K01-E)
This project was developed by students of Informatics ITB 2024:
| Name | NIM | Main Role |
| :--- | :--- | :--- |
| Samuelson Dharmawan Tanuraharja | 13524001 | Map Design, User & Queue Management |
| Muhammad Rafi Akbar | 13524125 | Login/Register, Diagnosis, Treatment, Check-up |
| Natanael I. Manurung | 13524021 | Basic ADT Implementation & Planning |
| Rhenaldy Cahyadi Putra | 13524039 | Logout, Password Reset, Patient Features |
| Miguel Rangga Deardo Sinaga | 13524069 | Help Menu, Load/Save Data, Exit |