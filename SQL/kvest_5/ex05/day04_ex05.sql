CREATE view v_price_with_discount as
SELECT person.name, menu.pizza_name, menu.price, round(menu.price*0.9) as discount_price from person
	join person_order on person_order.person_id = person.id
    	join menu on person_order.menu_id = menu.id
        order by name, pizza_name