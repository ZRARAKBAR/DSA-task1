# Operation Flow Explanation  
## Warehouse Inventory Alert System

---

## 1. Add New Product  
**What it does:**  
Lets the user insert a new warehouse product with ID, name, category, and quantity.

**Data Structure:**  
Singly Linked List

**Why this structure:**  
• Dynamic storage  
• Efficient insertion  
• Ideal for growing product lists  

**User Interaction:**  
User chooses “Add Product”, enters details, and the product is inserted at the end or start of the list.

---

## 2. Low Stock Alert  
**What it does:**  
Identifies all products with quantity lower than a threshold (e.g., < 10).

**Data Structure:**  
Linked List traversal

**Why this structure:**  
Since all products exist inside a linked list, a simple traversal efficiently checks each product’s quantity.

**User Interaction:**  
User selects “Low Stock Alert”, enters threshold, and the system displays all items below that limit.

---

## 3. Undo Last Operation (Final Version)  
**What it does:**  
Reverses the last user action such as Add, Delete, or Update.

**Data Structure:**  
Stack

**Why this structure:**  
Stacks allow Last-In-First-Out behavior, which perfectly matches undo operations.

**User Interaction:**  
User clicks “Undo”, and the system pops the last operation from the stack and reverses it.
