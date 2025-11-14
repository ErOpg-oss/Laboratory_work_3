SELECT * FROM categories
JOIN dishes ON categories.category_id = dishes.category_id
WHERE categories.category_name = 'Завтраки';