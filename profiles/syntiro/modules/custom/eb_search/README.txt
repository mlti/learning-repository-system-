== Description ==

This module allows you to Search the data

== Pre-requisites ==

ApacheSolr Module
Can work only on Edubridge
Google CSE


== Configuration ==

- There are several settings that can be configured in the following places:

  Administer > Site building > Modules (admin/build/modules)
    Capture weightage for the following:

    Used as part of a New Asset
    Used in curriculum
    Recommend by Teacher
    Recommend by Student
    Rating


Details 	                    Number	    Weightage	    Total
Asset used in Curriculum            n1	            2.5             n1*25
Asset used in creating New Asset    n2	            1.5	            n2*15
Recommended by Teacher              n3	            2.0             n3*25
Recommended by Student              n4	            1	            n4*10
Bookmarked by Teacher	            n5	            2.0             n5*20
Bookmarked by Student	            n6	            1	            n6*10

Rated by Teacher        Average Rating:rt	    2	            rt*2
Rated by Student	Average Rating:rs	    1	            rs*1




Score == (  ((n1*25)+(n2*15)+(n3*25)+(n4*10)+(n5*20)+(n6*10)) + rt*2 + rs*1 )/1n+2rt+1rt


   Administer > User management > Permissions (admin/user/permissions)

== ApacheSolr ==

Recommendations:
    hook_form_alter()

SCORING to be enabled using: hook_apachesolr_modifyquery()
                             hook_apachesolr_update_index()
                             hook_solr_apachesolr_prepare_query()
                             hook_apachesolr_node_exclude()

  hook_apachesolr_update_index()
    
    Assigning the Score value to the ps_score_content field
    
  
    
    
Function Name

        edubridge_search_result()
        eb_search_view()
        mars_search_results()

        hook_preprocess_edubridge_search()
        hook_preprocess_mars_search()

MenuCallbacks and TPLs

        $items['search/results']
        $items['mars/results']

        custom-search-result.tpl.php
        custom-search-results.tpl.php
        edubridge_search_result.tpl.php


Block ->
A) Search Block right-side-bar with results

   Resutls as links (5 items, Ajax pagination)

        Function Name

           getSolrSearchform_right()
           mysearch_results()
           hook_block()
           getSolrSearchform_right()
           mysearch_view()
           search_data_mysearch()

        MenuCallbacks and TPLs

           $items['mysearch/results']

           mysearch-results.tpl.php
           mysearch-search-results.tpl.php
           mysearch-search-result.tpl.php

B) Search Block header


C) Most Appropriate Resource Block

   Selct box (All, ... Interests and Subjects)
   Function Name
        getSolr_mars ()
        hook_block()

   Results as links
   Resutls as links (5 items, Ajax pagination)

== Federated Search & Google Search ==
    Function Name
        get_federatedSearch()
        custom_google_search()
        _google_cse_get_search_results_manual()
        google_xmlresults()
        getGoogleResult()
        eb_search_preprocess_search_results()

    MenuCallbacks and TPLs

        $items['search/results']

        google_xmlresults.tpl.php
        custom-search-result.tpl.php
        custom-search-results.tpl.php
        google_cse_xml_results.tpl.php
        
        
        
    Menucallback: popupsearch/results
    permission: access search
    Module: eb_search.inc
    Function: username_search()
    Todo: Set uid value in the checkbox. Redirect to submitted page with user id and insert username to specific textarea
         Popup: Searchbox submit and pagination should work in ajax. While select user and submit means popup should get closed and  post the username to specific textarea. Theming changes for textbox size and popup width. 
     
        username_search.tpl.php 
        username_search_result.tpl.php
        
        eb_search_preprocess_username_search()
        eb_search_preprocess_username_search_result()
        getSolrSearchform_header()
        username_select_form()
        
        File: eb_search2.js
          submit function  :
             Get selected username from for each.. and close the popup using drupal.popup.close() and Post the usernames to the textarea. 
        
