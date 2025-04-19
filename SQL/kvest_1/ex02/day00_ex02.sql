SELECT name, rating
from pizzeria
where rating >= 3.5 and rating <= 5.0
ORDER by rating ASC

SELECT name, rating
from pizzeria
where rating BETWEEN 3.5 and 5.0
ORDER by rating