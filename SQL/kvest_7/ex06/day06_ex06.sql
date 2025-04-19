CREATE SEQUENCE seq_person_discounts
START WITH 1
INCREMENT BY 1;

SELECT setval('seq_person_discounts', ((SELECT COUNT(*) from person_discounts) + 1));

alter table person_discounts
alter COLUMN discount set DEFAULT nextval('seq_person_discounts');