# Pseudocode.md  
## Warehouse Inventory Alert System – Pseudocode

---

### 1. AddProduct()
FUNCTION AddProduct(id, name, qty):
    newNode = CREATE Node
    newNode.id = id
    newNode.name = name
    newNode.qty = qty
    newNode.next = head
    head = newNode
END FUNCTION

---

### 2. UpdateProduct()
FUNCTION UpdateProduct(id, newQty):
    current = head
    WHILE current IS NOT NULL:
        IF current.id == id:
            current.qty = newQty
            RETURN
        ENDIF
        current = current.next
    ENDWHILE
    PRINT "Product Not Found"
END FUNCTION

---

### 3. DeleteProduct()
FUNCTION DeleteProduct(id):
    current = head
    prev = NULL

    WHILE current IS NOT NULL:
        IF current.id == id:
            IF prev == NULL:
                head = current.next
            ELSE:
                prev.next = current.next
            ENDIF
            DELETE current
            RETURN
        ENDIF
        prev = current
        current = current.next
    ENDWHILE
END FUNCTION

---

### 4. DisplayLowStock()
FUNCTION DisplayLowStock(threshold):
    current = head
    WHILE current IS NOT NULL:
        IF current.qty < threshold:
            PRINT current.id, current.name, current.qty
        ENDIF
        current = current.next
    ENDWHILE
END FUNCTION

---

### 5. UndoOperation()   // Final version
FUNCTION UndoOperation():
    IF undoStack IS EMPTY:
        PRINT "Nothing to undo"
        RETURN
    lastOp = undoStack.POP()
    PERFORM Reverse(lastOp)
END FUNCTION
