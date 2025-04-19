SELECT 
	m1.pizza_name,
    p1.name as pizzeria_name1,
    p2.name as pizzeria_name2,
    m1.price
from 
	menu m1 
JOIN 
	menu m2 on m1.pizza_name = m2.pizza_name and m1.price = m2.price
join
	pizzeria p1 on p1.id = m1.pizzeria_id
join 
	pizzeria p2 on p2.id = m2.pizzeria_id
where p1.name > p2.name
order by 1