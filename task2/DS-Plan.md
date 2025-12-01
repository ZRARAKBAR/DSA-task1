# DS-Plan.md  
## Warehouse Inventory Alert System – Data Structure Planning

This document outlines the core data structures used in the Warehouse Inventory Alert System and the reasoning behind each choice. The system is aligned with the project proposal and mid-term scope.

---

### 1. Product Storage  
**Data Structure:** Singly Linked List  
**Reason:**  
The number of products in a warehouse can grow dynamically.  
A linked list supports:  
• Efficient insertion and deletion  
• Dynamic memory allocation  
• Easy traversal for display, search, and low-stock alerts  

---

### 2. Update Product Quantity  
**Data Structure:** Linked List Traversal  
**Reason:**  
Since all products are stored in a linked list, updating a product requires locating it by its ID or name.  
Traversal is simple and efficient for mid-term requirements.

---

### 3. Delete a Product  
**Data Structure:** Singly Linked List  
**Reason:**  
Deleting nodes from a linked list is efficient: only pointer adjustments are required.  
This avoids shifting elements (as in arrays).

---

### 4. Low Stock Alert Generation  
**Data Structure:** Linked List Traversal  
**Reason:**  
Mid-term version does not require heaps or advanced structures.  
A simple traversal is enough to identify all products below the stock threshold.

---

### 5. Undo/Redo Operation (Final Version)  
**Data Structure:** Stack  
**Reason:**  
Stacks naturally support Last-In-First-Out behavior, which is ideal for:  
• Undo last action  
• Redo undone actions  
Each user operation is pushed into the stack to allow reversal.

---

### Summary  
• **Linked List → Core inventory management**  
• **Stacks → Undo/Redo in final GUI version**  
• **Arrays (optional) → Temporary sorting & reports (final)**  

This plan ensures strong alignment with the project proposal and DSA concepts.
