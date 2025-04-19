(
  SELECT order_date as action_date, name as person_name from person_order
	inner join person
 	on person.id = person_order.person_id
)
INTERSECT
(
  SELECT visit_date as action_date, name as person_name from person_visits
  	inner join person
  	on person.id = person_visits.person_id
)
ORDER by action_date, person_name desc