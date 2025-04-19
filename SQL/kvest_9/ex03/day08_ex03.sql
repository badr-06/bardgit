--Session #1
begin transaction isolation level repeatable read;
select rating from pizzeria where name like 'Pizza Hut';
select rating from pizzeria where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';

--Session #2
begin transaction isolation level repeatable read;
update pizzeria set rating = 3.6 where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';
