SELECT menu.pizza_name, menu.price, pizzeria.name from menu
	join pizzeria on pizzeria.id = menu.pizzeria_id
WHERE menu.id not in (
  SELECT menu_id FROM person_order
  )
  order by 1, 2, 3