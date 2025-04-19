SET enable_seqscan = OFF;
EXPLAIN ANALYZE
SELECT pizza_name, pizzeria.name as pizzeria_name from pizzeria
	join menu on menu.pizzeria_id = pizzeria.id