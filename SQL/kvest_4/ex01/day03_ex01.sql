SELECT menu.id from menu
WHERE menu.id not in (
  SELECT menu_id FROM person_order
  )
ORDER by 1