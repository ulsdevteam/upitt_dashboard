# upitt_dashboard



## Usage
Simply login with an account that has permission to view the University of Pittsburgh Admin Dashboard.  The dashboard will appear on the /user page if you have the correct permissions.


Example block would be something like this Title: "WebServices needs to add TN_LARGE" 
SOLR query: `http://gamera.library.pitt.edu/solr/select?q=(PID:pitt\:*)%20AND%20(RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:bookCModel)&fl=*&fq=-fedora_datastream_latest_TN_LARGE_ID_ms:[*%20TO%20*]&rows=5` 
link 1: the collection
link 2: the datastreams manage page


from barnard islandora utilities stats-contentmodel-counts.php
/ # total counts of each model type -- broken down by PID (pitt:*, {not "pitt"}:*
/ # could be enhanced to run same report since a given date

from barnard islandora utilities stats-created-counts.php
/ # per collection, it will display the # of items of each model type
/ # could be enhanced to run same report since a given date

Orphan page report - 6
`http://gamera.library.pitt.edu/solr/select?q=(PID:pitt\:*)%20AND%20-RELS_EXT_isPageOf_uri_s:[%22%22%20TO%20*]%20AND%20RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:pageCModel*)&fl=PID,fedora_datastreams_ms,isMemberOfSite,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms&rows=100&wt=csv`

Orphan manuscript ("Book") report 1350 
`http://gamera.library.pitt.edu/solr/select?q=(PID:pitt\:*)%20AND%20-RELS_EXT_isMemberOfCollection_uri_s:[%22%22%20TO%20*]%20AND%20RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:bookCModel*)&fl=PID,RELS_EXT_hasModel_uri_s,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s&rows=1500&wt=csv`

Orphaned images report 134
`http://gamera.library.pitt.edu/solr/select?q=(PID:pitt\:*)%20AND%20-RELS_EXT_isMemberOfCollection_uri_s:[%22%22%20TO%20*]%20AND%20RELS_EXT_hasModel_uri_s:(*sp_large_image_cmodel*)&fl=PID,RELS_EXT_hasModel_uri_s,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s&rows=1500&wt=csv`

all items in a given collection
`http://gamera.library.pitt.edu/solr/select?q=(PID:pitt\:*)%20AND%20RELS_EXT_isMemberOfCollection_uri_ms:info\:fedora\/pitt\:collection.11&fl=PID,RELS_EXT_hasModel_uri_s,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s&rows=17000&wt=csv`

## Author / License

Written by [Willow Gillingham](https://github.com/bgilling) for the [University of Pittsburgh](http://www.pitt.edu).  Copyright (c) University of Pittsburgh.

Released under a license of GPL v2 or later.
