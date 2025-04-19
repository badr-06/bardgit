INSERT into menu(id, pizzeria_id, pizza_name, price)
VALUES(
  (SELECT max(id)+1 from menu), 
  (SELECT pizzeria.id from pizzeria
   WHERE pizzeria.name like 'Dominos'),
  'sicilian pizza',
   900   
  )