SELECT 
	person.address, 
	round((mAX(person.age)::decimal - (MIN(person.age)::decimal/max(person.age)::DECIMAL)), 2) as formula, 
	round(avg(person.age), 2) as average_age,
    CASE
    	when (mAX(person.age) - (MIN(person.age)/max(person.age))) > avg(person.age) then true
        else false
    end as comparison
from
	person
GROUP by person.address
order by 1