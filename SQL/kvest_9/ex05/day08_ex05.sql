--Session #1
begin transaction isolation level read committed;
select rating from pizzeria where name like 'Pizza Hut';
select rating from pizzeria where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';

--Session #2
begin transaction isolation level read committed;
insert into pizzeria (id, name, rating) values (10, 'Kazan Pizza', 5);
commit;
select rating from pizzeria where name like 'Pizza Hut';