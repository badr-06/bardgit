SET enable_seqscan = OFF;
EXPLAIN ANALYZE
SELECT name from person 
where UPPER(name) = 'ANNA'