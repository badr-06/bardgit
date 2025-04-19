SELECT person.address, pizzeria.name, COUNT(*) as count_of_orders 
from 
	person 
JOIN 
	person_order on person_order.person_id = person.id
join 
	menu on person_order.menu_id = menu.id
JOIN
	pizzeria on menu.pizzeria_id = pizzeria.id
GROUP by person.address, pizzeria.name
order by 1, 2