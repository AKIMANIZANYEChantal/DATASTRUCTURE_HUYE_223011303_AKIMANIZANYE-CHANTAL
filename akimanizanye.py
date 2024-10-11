from collections import deque

class OnlineShoppingPlatform:
    def __init__(self):
        self.recently_added = []  # Stack for recently added items
        self.checkout_queue = deque()  # Queue for processing checkout orders
        self.shopping_cart = []  # List for managing the shopping cart

    def add_item(self, item):
        self.shopping_cart.append(item)
        if len(self.recently_added) >= 5:
            self.recently_added.pop()
        self.recently_added.insert(0, item)

    def remove_item(self, item):
        if item in self.shopping_cart:
            self.shopping_cart.remove(item)

    def view_recently_added(self):
        return self.recently_added

    def add_to_checkout_queue(self, order):
        self.checkout_queue.append(order)

    def process_next_order(self):
        if self.checkout_queue:
            return self.checkout_queue.popleft()
        return None

    def view_shopping_cart(self):
        return self.shopping_cart

# Example usage
platform = OnlineShoppingPlatform()

# Adding items to the cart
platform.add_item("Laptop")
platform.add_item("Mouse")
platform.add_item("Keyboard")
platform.add_item("Monitor")
platform.add_item("Headphones")
platform.add_item("Webcam")

print("Recently added items:", platform.view_recently_added())
print("Shopping cart:", platform.view_shopping_cart())

# Removing an item
platform.remove_item("Mouse")
print("Shopping cart after removing Mouse:", platform.view_shopping_cart())

# Adding orders to the checkout queue
platform.add_to_checkout_queue("Order 1")
platform.add_to_checkout_queue("Order 2")
platform.add_to_checkout_queue("Order 3")

# Processing orders
print("Processing order:", platform.process_next_order())
print("Processing order:", platform.process_next_order())

print("Final shopping cart:", platform.view_shopping_cart())
print("Final recently added items:", platform.view_recently_added())