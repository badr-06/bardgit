SELECT person1.name as person_name1, person2.name as person_name2, person1.address as common_address from person person1
	join person person2 on person1.address = person2.address and person1.id > person2.id
order by 1, 2, 3