SELECT
	person.name as person_name, 
    menu.pizza_name,
    price, 
    price - ((price * discount)/100)::int as discount_price,
    pizzeria.name as pizzeria_name
from 
	person
   	INNER join person_order on person_order.person_id = person.id
    inner join menu on person_order.menu_id = menu.id
    inner join person_discounts on person_discounts.person_id = person.id and person_discounts.pizzeria_id = menu.pizzeria_id
    inner join pizzeria on pizzeria.id = menu.pizzeria_id
order by 1, 2