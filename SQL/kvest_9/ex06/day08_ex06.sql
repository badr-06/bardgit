--Session #1
begin transaction isolation level repeatable read;
select rating from pizzeria where name like 'Pizza Hut';
select rating from pizzeria where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';

--Session #2
begin transaction isolation level repeatable read;
insert into pizzeria (id, name, rating) values (11, 'Kazan Pizza 2', 4);
commit;
select rating from pizzeria where name like 'Pizza Hut';