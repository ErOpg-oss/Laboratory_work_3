CREATE TABLE categories (
    category_id INT PRIMARY KEY,              
    category_name VARCHAR(100) NOT NULL UNIQUE 
);


CREATE TABLE dishes (
    id INT PRIMARY KEY,       
    name VARCHAR(200) NOT NULL,              
    category_id INT NOT NULL REFERENCES categories(category_id), 
    price DECIMAL(8, 2) NOT NULL CHECK (price > 0)     
);


CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,            
	dish_id INT NOT NULL REFERENCES dishes(id),
    order_date DATE NOT NULL DEFAULT CURRENT_DATE,
    quantity INT NOT NULL CHECK (quantity > 0),    
    total_price DECIMAL(10, 2) NOT NULL CHECK (total_price >= 0)
);