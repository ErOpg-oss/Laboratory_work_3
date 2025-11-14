UPDATE dishes
SET price = price*1.5
FROM categories
WHERE dishes.category_id = categories.category_id AND categories.category_name = 'Закуски';