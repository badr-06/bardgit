SELECT (SELECT name from person WHERE person.id = person_order.person_id) as person_name,
case (SELECT name from person WHERE person.id = person_order.person_id)
	when 'Denis' then true
	else false
end as check_name
from person_order
where (menu_id = 13 or menu_id = 14 or menu_id = 18) and (order_date = '2022-01-07')
