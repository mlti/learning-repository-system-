== Description ==

My MARS Page
My MARS Basket
My MARS Alerts

My MARS Page and Basket display 2 links for every Discipline in user's profile
(one Top Edubridge result and one Latest result for each Discipline)

1 - Add NEW field Discipline to the Profile information. This has to be a Taxonomy field. Please use Profile Taxonomy Module.

2 - On Cron for every Discipline we need to obtain: Most Appropriate result from the Apache Solr search for that Discipline category and the Latest
result for that category with in the LAST 1 month. Store in mars_discipline table. We must be able to capture the sequence as well. ( Tomorrow we may want to show 3 for wach discipline instead of 2, store n as a variable) (LAST 1 month should also be in a separate variable, can be configured)

MARS results must be duration/period based unlike the main search result page, so we throw up more current results in MARS. -> Have a frequency set and on Cron run if this is expired, clear and refresh MARS data.

mars_discipline table:id, discipline-tid, type (edu-top-rank or latest), created, weight

-- Function to retrieve results from Apache Solr
-- Function in Cron to delete enties based on timestamp and refresh Taxonomy wise MARS information in the mars_discipline table
-- INSERT QUERY to mars_discipline table

3 - Statistics:
There must be an entry in this Table if the user clicks on his MARS link. mars_statistics: assetID, uid, rid, Timestamp

When a user clicks on a link update this table, store last accessed node here.
INSERT QUERY


4 - My MARS menu callback ->  
-- Permissions: Access my mars

The User must be presented one latest link and one edu-top link for each discipline on his MARS page. The links that have been accessed
must have a different class assoc. with it. The My MARS page must be constructed based on if there is an entry in the MY MARS statistics table or not. (this is to indicate new vs visited links using a css class)
-- SELECT QUERY

5 - My MARS Basket
  - My MARS Homepage Block Content using Hook Block


REPORTS: TODO