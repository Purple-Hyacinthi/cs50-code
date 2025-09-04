SELECT AVG(rating) AS average_rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id  -- 正确连接位置(只能在FROM后)
WHERE movies.year = 2012;
