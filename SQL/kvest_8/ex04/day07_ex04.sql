SELECT 
	person.name, 
    COUNT(*) as count_of_visits 
from 
	person_visits
JOIN 
	person on person_visits.person_id = person.id
GROUP by
	person.name
HAVING 
	COUNT(*) > 3