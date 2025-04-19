COMMENT on TABLE person_discounts is 'Таблица скидок для клиентов.';
COMMENT on COLUMN person_discounts.id is 'Внутренний ключ';
COMMENT on COLUMN person_discounts.person_id is 'внешний ключ таблицы person';
COMMENT on COLUMN person_discounts.pizzeria_id is 'Внешний ключ таблицы pizzeria';
COMMENT on COLUMN person_discounts.discount is 'скидка в процентах для клиента';