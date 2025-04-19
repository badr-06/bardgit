SELECT person.name from person_order
	join menu on person_order.menu_id = menu.id
    	join person on person_order.person_id = person.id where menu.pizza_name like 'pepperoni%' and person.gender = 'female'
INTERSECT
SELECT person.name from person_order
	join menu on person_order.menu_id = menu.id
    	join person on person_order.person_id = person.id where menu.pizza_name like 'cheese%' and person.gender = 'female'
ORDER by name