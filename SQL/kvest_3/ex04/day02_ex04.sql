SELECT menu.pizza_name, pizzeria.name as pizzeria_name, menu.price from menu
	join pizzeria on pizzeria.id = menu.pizzeria_id
    where pizza_name like 'pepperoni%' or pizza_name LIKE 'mushroom%'
ORDER by pizza_name, pizzeria_name