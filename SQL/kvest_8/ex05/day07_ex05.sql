SELECT 
	DISTINCT person.name 
FROM
	person_visits
JOIN
	person on person_visits.person_id = person.id
order by 1