SELECT dishes.name, SUM(orders.quantity) AS popular_dishes
FROM dishes, orders
WHERE orders.dish_id = dishes.id
GROUP BY dishes.name
ORDER BY popular_dishes DESC;