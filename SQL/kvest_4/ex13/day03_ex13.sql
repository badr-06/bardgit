DELETE from person_order 
where person_order.menu_id = (SELECT id from menu where menu.pizza_name like 'greek pizza');

DELETE from menu
where menu.pizza_name like 'greek pizza'