# KISAN MARKET: A FARMER CENTRIC MARKETPLACE  
*(Data Structures & Algorithms)* 

---


**Institution:**  
Gati Shakti Vishwavidyalaya  
*A Central University, Under the Ministry of Railways, Government of India*  
Vadodara, Gujarat  

---

## INDEX
1. **Introduction**  
   1.1 Overview  
   1.2 Problem Statement  

2. **Modules of the Project**  
   2.1 Functionality  
   - Farmer Management  
   - Bidder Management  
   - Bid Management  
   - Users of the System  

3. **Data Structures & Algorithms**  
   - Data Structures Used  
   - CSV Files for Persistent Storage  
   - Algorithms Used  
   - File Operations  
   - Input  
   - Processing  
   - Output  

4. **Project Execution**  
   - Main Interface  
   - Add Farmer  
   - Add Bidder  
   - Display Farmers  
   - Display Bidders  
   - Deleting a Farmer  
   - Deleting a Bidder  
   - Updating a Farmer  
   - Updating a Bidder  
   - Displaying Highest Bids  

5. **Conclusion & Future Work**  
   - Conclusion  
   - Future Work  
     - Web Interface Development  
     - Automated Notifications  
     - Enhanced Analytics  
     - Integration with Online Payment Gateways  
     - Blockchain Integration  

---

## 1. Introduction
### 1.1 Overview
The Farmer Management System is a software application tailored for managing interactions between farmers and bidders. This system digitizes the process of managing farmer data, bids, and transactions, ensuring a clear view of crop availability and bidding activity.  

### 1.2 Problem Statement
Traditional crop-selling methods are often inefficient. This system aims to bridge this gap by providing a platform for transparent and competitive bidding, empowering farmers and bidders with better opportunities.

---

## 2. Modules of the Project
### 2.1 Functionality
#### 2.1.1 Farmer Management
- Add, update, display, and delete farmer records.  
#### 2.1.2 Bidder Management
- Add, update, display, and delete bidder records.  
#### 2.1.3 Bid Management
- Manage bids using a priority queue to identify the highest bids quickly.  
#### 2.1.4 Users of the System
- Farmers: Register crop details.  
- Bidders: Place competitive bids.

---

## 3. Data Structures & Algorithms
### 3.1 Data Structures Used
- Structs for farmers, bidders, and bids.  
- Priority Queue for managing bids.  

### 3.2 CSV Files for Persistent Storage
- `farmers.csv` and `bidders.csv` for saving records.  

### 3.3 Algorithms Used
- Priority queue insertion (O(n)) for bid organization.  

### 3.4 File Operations
- Save and load operations for CSV files.  

### 3.5 Input
- Farmer and bidder data.  

### 3.6 Processing
- Bids are sorted in descending order.  

### 3.7 Output
- Reports on farmers, bidders, and the highest bids.

---

## 4. Project Execution
### 4.1 Main Interface
- A menu-driven interface for easy navigation.  

### 4.2 Add Farmer / Bidder  
- Add farmer/bidder details and save to `farmers.csv` or `bidders.csv`.  

### 4.3 Display Farmers / Bidders
- List all registered farmers or bidders.  

### 4.4 Delete / Update Farmer or Bidder
- Remove or modify farmer/bidder details from the system.  

### 4.5 Displaying Highest Bids
- Show the highest bids for each crop.

---

## 5. Conclusion & Future Work
### 5.1 Conclusion
The system simplifies farmer-bidder interactions and provides a transparent bidding process.  

### 5.2 Future Work
- **Web Interface Development**: Create an accessible web-based platform.  
- **Automated Notifications**: Real-time updates via email/SMS.  
- **Enhanced Analytics**: Insights into bid patterns and market trends.  
- **Integration with Online Payment Gateways**: Secure transactions.  
- **Blockchain Integration**: Enhance security and transparency.

---
