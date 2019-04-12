CREATE TABLE	test_geom ( id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  							name TEXT NOT NULL,
  							measured_value DOUBLE NOT NULL);

SELECT AddGeometryColumn('test_geom', 'the_geom', 4326, 'POINT', 'XY');

INSERT INTO test_geom(id, name, measured_value, the_geom) VALUES (NULL, 'first point', 1.23456, GeomFromText('POINT(1.01 2.02)', 4326));
INSERT INTO test_geom VALUES (NULL, 'second point', 2.34567, GeomFromText('POINT(2.02 3.03)', 4326));
INSERT INTO test_geom (id, name, measured_value, the_geom) VALUES (10, 'tenth point', 10.123456789, GeomFromText ('POINT(10.01 10.02)', 4326));
INSERT INTO test_geom (the_geom, measured_value, name, id) VALUES (GeomFromText('POINT(11.01 11.02)', 4326), 11.123456789, 'eleventh point', NULL);