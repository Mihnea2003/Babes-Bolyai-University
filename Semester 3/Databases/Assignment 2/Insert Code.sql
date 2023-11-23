--1.Inserting in the Bosses Table
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(1,'Mihnea',9999);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(2,'Madalina',1000);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(5,'Badea',50);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(4,'Gabi',456);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(7,'Mike',99);
--2.Inserting in the Buyers Table
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(22,200,11.02,'Pipera');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(23,200,11.02,'Sighisoara');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(25,0,01.02,'Marasti');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(20,207,11.06,'Gheorgheni');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(12,250,05.90,'Cotroceni');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(662,600,10.00,'Marasti');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(100,1200,07.08,'Gheorgheni');

--3.Inserting in the Shops Table
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(10,1,22,'Pipera','10:34:09 AM','22:34:09')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(11,2,22,'Cotroceni','10:00:00 AM','20:00:00')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(12,5,25,'Marasti','12:00:00 ','22:00:00')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(13,4,100,'Gheorgheni','12:00:00 AM','19:00:00')

--INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
--VALUES(10,4,100,'Gheorgheni','12:00:00 AM','19:00:00') error primary key
--4.Inserting in the Sites Table
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(33,100,500,'The first Site with more shops than you know') 
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(30,10,50,'This site has the best prices')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(31,30,150,'More shops than you will ever find')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(32,50,250,'The best in the industry')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(34,50,250,'The coziest shop')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(35,60,300,'The best of the best')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(36,50,250,'If you dont find a shop on our site,will give you 50$')

--5.Inserting in the ExistIn Table
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(12,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,34);
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,30);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,32);
INSERT INTO ExistIn(shops_id,sites_id)
Values(12,36);
INSERT INTO ExistIn(shops_id,sites_id)
Values(13,32);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,34);
INSERT INTO ExistIn(shops_id,sites_id)
Values(13,35);
-- Insert into the Sellers table with unique sellers_id and specified seller names
INSERT INTO Sellers (sellers_id, seller_name, location, birth_date, shops_id)
VALUES
(11, 'Ioana', 'Location 1', '1990-01-15', 1),
(12, 'Maria', 'Location 2', '1985-03-20', 2),
(13, 'Mada', 'Location 3', '1995-07-10', 3),
(14, 'Ion', 'Location 4', '1980-11-25', 1),
(15, 'Gorji', 'Location 5', '1988-09-12', 2);

-- Insert into the PossessIt table with unique sellers_id and cleaning_sets_id
INSERT INTO PossessIt (sellers_id, )
VALUES
(11, 21),
(12, 22),
(13, 23),
(14, 24),
(15, 25);

-- Insert into the Cleaning_sets table with unique cleaning_sets_id
INSERT INTO Cleaning_sets (cleaning_sets_id, price, brand, sellers_id, efficiency)
VALUES
(21, 25, 'Brand 21', 11, 90),
(22, 30, 'Brand 22', 12, 95),
(23, 20, 'Brand 23', 13, 85),
(24, 35, 'Brand 24', 14, 92),
(25, 28, 'Brand 25', 15, 88);

-- Insert into the Shoes table with unique shoes_id
INSERT INTO Shoes (shoes_id, sellers_id, type, color, size, cost)
VALUES
(31, 11, 'Sneakers', 'Blue', 9, 50),
(32, 12, 'Boots', 'Brown', 8, 65),
(33, 13, 'Sandals', 'Black', 7, 40),
(34, 14, 'Running Shoes', 'Red', 10, 55),
(35, 15, 'Dress Shoes', 'Black', 9, 70);

-- Insert into the HaveIt table with unique sellers_id and shoes_id
INSERT INTO HaveIt (sellers_id, shoes_id)
VALUES
(11, 31),
(12, 32),
(13, 33),
(14, 34),
(15, 35);

