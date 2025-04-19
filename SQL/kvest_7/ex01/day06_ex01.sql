INSERT into person_discounts (id, person_id, pizzeria_id, discount)
SELECT 
	ROW_NUMBER() over() as id,
    person_id,
    pizzeria_id,
    CASE
    	when count(*) = 1 then 10.5
        when COUNT(*) = 2 then 22
        ELSE 30
	end as discount
   FROM person_order
   	 inner JOIN menu on person_order.menu_id = menu.id
  GROUP by person_id, pizzeria_id;
  