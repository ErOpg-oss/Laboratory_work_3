DELETE FROM orders
USING dishes
WHERE orders.dish_id = dishes.id AND dishes.name = 'Котлета "От шефа"';

DELETE FROM dishes
WHERE dishes.name = 'Котлета "От шефа"'