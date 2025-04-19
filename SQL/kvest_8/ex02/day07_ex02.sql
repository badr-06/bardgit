( SELECT 
	pizzeria.name, 
    COUNT(*) as count,
    'order' as action_type
from pizzeria
join menu on menu.pizzeria_id = pizzeria.id
join person_order on person_order.menu_id = menu.id
GROUP by pizzeria.name
order by 2 desc, 1
LIMIT 3 )

UNION

(SELECT 
	pizzeria.name, 
    COUNT(*) as count,
    'visit' as action_type
from person_visits
join pizzeria on pizzeria.id = person_visits.pizzeria_id
GROUP by pizzeria.name
order by 2 desc, 1
LIMIT 3)
ORDER by 3, 2 desc