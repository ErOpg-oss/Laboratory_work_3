SELECT categories.category_name, SUM(orders.total_price) AS revenue
FROM categories, dishes, orders
WHERE orders.dish_id = dishes.id and dishes.category_id = categories.category_id
GROUP BY categories.category_name
ORDER BY revenue DESC;