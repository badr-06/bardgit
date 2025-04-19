SELECT 
	pizzeria.name,
    COUNT(*) as count_of_orders,
    case 
    	WHEN avg(menu.price) = FLOOR(avg(menu.price)) then round(avg(menu.price))
        else round(avg(menu.price), 2)
    end as average_price,
    max(menu.price) as max_price,
    min(menu.price) as min_price
from 
	pizzeria
JOIN
	menu on menu.pizzeria_id = pizzeria.id
join 
	person_order on person_order.menu_id = menu.id
GROUP by pizzeria.name
order by 1