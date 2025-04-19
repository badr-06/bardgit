INSERT into person_order(id, person_id, menu_id, order_date)
values(
  	(SELECT max(id)+1 from person_order),
  	(SELECT id from person where person.name like 'Denis'),
  	(SELECT id from menu where menu.pizza_name like 'sicilian pizza'),
  	'2022-02-24'
   ),
   (
    (SELECT max(id)+2 from person_order),
  	(SELECT id from person where person.name like 'Irina'),
  	(SELECT id from menu where menu.pizza_name like 'sicilian pizza'),
  	'2022-02-24'
   )