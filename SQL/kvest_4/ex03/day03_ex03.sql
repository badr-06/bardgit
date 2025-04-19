SELECT pz.pizzeria_name from (
   SELECT pizzeria.name as pizzeria_name from person_visits
	join person on person.id = person_visits.person_id and person.gender like 'female'
		join pizzeria on pizzeria.id = person_visits.pizzeria_id
EXCEPT ALL
SELECT pizzeria.name from person_visits
	join person on person.id = person_visits.person_id and person.gender like 'male'
		join pizzeria on pizzeria.id = person_visits.pizzeria_id
  ) as pz
UNION all
SELECT pz.pizzeria_name from (
  	 SELECT pizzeria.name as pizzeria_name from person_visits
	join person on person.id = person_visits.person_id and person.gender like 'male'
		join pizzeria on pizzeria.id = person_visits.pizzeria_id
EXCEPT ALL
SELECT pizzeria.name from person_visits
	join person on person.id = person_visits.person_id and person.gender like 'female'
		join pizzeria on pizzeria.id = person_visits.pizzeria_id
  ) as pz   
ORDER by pizzeria_name