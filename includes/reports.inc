<?php

/** Unit to store the content functions related to each report
 *
 */

define('CST_ITEMS_PER_PAGE', 20);

function upitt_dashboard_contentObjectsCsv_getcount($csv = FALSE, $page = 0, $all = FALSE) {
  $q = '(PID:pitt\:*) AND -(RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:pageCModel OR RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:manuscriptPageCModel OR RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:collectionCModel)';
  return _get_numFound($q, $fq);
}

function upitt_dashboard_contentObjectsCsv_content($csv = FALSE, $page = 0, $all = FALSE) {
  set_time_limit(0);
  $delta = 'contentObjectsCsv';
  $subject = 'Content Objects report';
  $q = '(PID:pitt\:*) AND -(RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:pageCModel OR RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:manuscriptPageCModel OR RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:collectionCModel)';
  $fq = "";

  $fl = "PID,mods_originInfo_dateCreated_ms,mods_originInfo_dateIssued_ms,mods_originInfo_type_display_dateOther_ms,mods_originInfo_type_sort_dateOther_ms,mods_originInfo_place_placeTerm_text_ms," .
        "mods_accessCondition_copyright_copyright_status_ms,mods_accessCondition_copyright_publication_status_ms,mods_accessCondition_copyright_general.note_ms,mods_accessCondition_copyright_rights.holder_name_ms," .
        "mods_accessCondition_copyright_rights.holder_note_ms,mods_abstract_ms,mods_subject_topic_ms,mods_subject_geographic_ms,mods_subject_name_conference_namePart_ms,mods_subject_hierarchicalGeographic_city_ms," .
        "mods_subject_hierarchicalGeographic_citySection_ms,mods_subject_hierarchicalGeographic_county_ms,mods_subject_temporal_ms,mods_subject_occupation_ms,mods_subject_titleInfo_title_ms,mods_subject_genre_ms," .
#        "mods_name_namePart_ms,
#        "mods_name_role_roleTerm_text_ms,
        // new MODS fields next line
        "mods_name_creator_namePart_ms,mods_name_contributor_namePart_ms,mods_name_depositor_namePart_ms,RELS-EXT_isMemberOfCollection_uri_ms,RELS-EXT_isMemberOfSite_uri_ms," . 
        "mods_relatedItem_titleInfo_title_ms,mods_relatedItem_host_note_prefercite_ms,mods_titleInfo_nonSort_ms,mods_titleInfo_title_ms," .
        "mods_titleInfo_subTitle_ms,mods_titleInfo_partNumber_ms,mods_titleInfo_partName_ms,mods_note_address_ms,mods_physicalDescription_form_ms,mods_identifier_pitt_ms,mods_identifier_local_ms," .
        "mods_typeOfResource_ms,mods_genre_ms,mods_language_languageTerm_code_authority_iso639-2b_ms,mods_language_languageTerm_code_ms,dc.title,dc.rights,dc.coverage,dc.subject," . 
        // new DC fields next line 
        "dc.contributor,dc.creator,dc.date,dc.description,dc.format,dc.subject,dc.type";

  $headings = array('PID' => 'fedora_object_pid',
                    'mods_originInfo_dateCreated_ms' => 'mods_originInfo_dateCreated',
                    'mods_originInfo_dateIssued_ms' => 'mods_originInfo_dateIssued',
                    'mods_originInfo_type_display_dateOther_ms' => 'mods_originInfo_dateOther_display',
                    'mods_originInfo_type_sort_dateOther_ms' => 'mods_originInfo_dateOther_sort',
                    'mods_originInfo_place_placeTerm_text_ms' => 'mods_originInfo_place',
                    'mods_accessCondition_copyright_copyright_status_ms' => 'mods_accessCondition_copyright_status',
                    'mods_accessCondition_copyright_publication_status_ms' => 'mods_accessCondition_publication_status',
                    'mods_accessCondition_copyright_general.note_ms' => 'mods_accessCondition_copyrightMD_general_note',
                    'mods_accessCondition_copyright_rights.holder_name_ms' => 'mods_accessCondition_copyrightMD_rights_holder_name',
                    'mods_accessCondition_copyright_rights.holder_note_ms' => 'mods_accessCondition_copyrightMD_rights_holder_contact',
                    'mods_abstract_ms' => 'mods_abstract',
                    'mods_subject_topic_ms' => 'mods_subject_topic',
                    'mods_subject_geographic_ms' => 'mods_subject_geographic',
                    'mods_subject_name_conference_namePart_ms' => 'mods_subject_name_namePart',
                    'mods_subject_hierarchicalGeographic_city_ms' => 'mods_subject_hierarchicalGeographic_city',
                    'mods_subject_hierarchicalGeographic_citySection_ms' => 'mods_subject_hierarchicalGeographic_citySection',
                    'mods_subject_hierarchicalGeographic_county_ms' => 'mods_subject_hierarchicalGeographic_county',
                    'mods_subject_temporal_ms' => 'mods_subject_temporal',
                    'mods_subject_occupation_ms' => 'mods_subject_occupation',
                    'mods_subject_titleInfo_title_ms' => 'mods_subject_titleInfo_title',
                    'mods_subject_genre_ms' => 'mods_subject_genre',
#                    'mods_name_namePart_ms' => 'mods_name_namePart',
#                    'mods_name_role_roleTerm_text_ms' => 'mods_name_role_roleTerm',
                    'mods_name_creator_namePart_ms' => 'mods_name_creator_namePart_ms',
                    'mods_name_contributor_namePart_ms' => 'mods_name_contributor_namePart_ms',
                    'mods_name_depositor_namePart_ms' => 'mods_name_depositor_namePart_ms',
                    'RELS-EXT_isMemberOfCollection_uri_ms' => 'RELS-EXT_isMemberOfCollection_uri_ms',
                    'RELS-EXT_isMemberOfSite_uri_ms' => 'RELS-EXT_isMemberOfSite_uri_ms',
                    'mods_relatedItem_titleInfo_title_ms' => 'mods_relatedItem_titleInfo_title',
                    'mods_relatedItem_host_note_prefercite_ms' => 'mods_relatedItem_note_prefercite',
                    'mods_titleInfo_nonSort_ms' => 'mods_titleInfo_nonSort',
                    'mods_titleInfo_title_ms' => 'mods_titleInfo_title',
                    'mods_titleInfo_subTitle_ms' => 'mods_titleInfo_subTitle',
                    'mods_titleInfo_partNumber_ms' => 'mods_titleInfo_partNumber',
                    'mods_titleInfo_partName_ms' => 'mods_titleInfo_partName',
                    'mods_note_address_ms' => 'mods_note_address',
                    'mods_physicalDescription_form_ms' => 'mods_physicalDescription_form',
                    'mods_identifier_pitt_ms' => 'mods_identifier_pitt',
                    'mods_identifier_local_ms' => 'mods_identifier_local',
                    'mods_typeOfResource_ms' => 'mods_typeOfResource',
                    'mods_genre_ms' => 'mods_genre',
                    'mods_language_languageTerm_code_authority_iso639-2b_ms' => 'mods_language_languageTerm_authority',
                    'mods_language_languageTerm_code_ms' => 'mods_language_languageTerm',
                    'dc.title' => 'dc_title',
                    'dc.rights' => 'dc_rights',
                    'dc.coverage' => 'dc_coverage',
                    'dc.subject' => 'dc_subject',
                    'dc.contributor' => 'dc.contributor',
                    'dc.creator' => 'dc.creator',
                    'dc.date' => 'dc.date',
                    'dc.description' => 'dc.description',
                    'dc.format' => 'dc.format',
                    'dc.subject' => 'dc.subject',
                    'dc.type' => 'dc.type',
                  );
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all); 
}

function upitt_dashboard_test1_getcount($csv = FALSE, $page = 0, $all = FALSE) {
  $q = '(PID:pitt\:*) AND -RELS_EXT_isPageOf_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:pageCModel*)';
  return _get_numFound($q, "");
}

function upitt_dashboard_test1_content($csv = FALSE, $page = 0, $all = FALSE) {
  $delta = 'test1';
  $subject = 'Orphan Page (BookCModel) report';
  $q = '(PID:pitt\:*) AND -RELS_EXT_isPageOf_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:pageCModel*)';
  $fq = "";
  $fl = "PID,fedora_datastreams_ms,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all);
}

function upitt_dashboard_django1_content($csv = FALSE, $page = 0, $all = FALSE) {
  // u=USERNAME,p=PASSWORD,h=HOST,db=DBNAME
  $delta = 'django1';
  $subject = 'Objects from `workflow_django` that are in Islandora';
  $headings = array('date' => 'Date',
                    'count' => 'Count',
                    'PID' => 'PID',
                    'model_desc' => 'Model');
  $sql = 'SELECT i.date, i.count, i.PID, m.model_desc ' .
         'FROM {islandora_stats_collection_models} i ' .
         'JOIN {islandora_stats_models} m ON (m.model_id = i.model_id) ' .
         'WHERE m.model_desc = \'Book\' ' .
         'ORDER BY i.date, i.PID, m.model_desc';
  return _get_SQL_report($delta, $subject, $sql, $headings, $csv, $page, $all, 'u=islandora,p=ulsislandora,h=bigfoot.library.pitt.edu,db=workflow_django');
}

function upitt_dashboard_test2_getcount($csv = FALSE, $page = 0, $all = FALSE) {
  $q = '(PID:pitt\:*) AND (RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:bookCModel)';
  return _get_numFound($q, "");
}

function upitt_dashboard_test2_content($csv = FALSE, $page = 0, $all = FALSE) {
  $delta = 'test2';
  $subject = 'WebServices needs to add TN_LARGE';
  $q = '(PID:pitt\:*) AND (RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:bookCModel)';
  $fq = "-fedora_datastream_latest_TN_LARGE_ID_ms:[* TO *]";
  $fl = "PID,fedora_datastreams_ms,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');

  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all);
}

function upitt_dashboard_islandora_collection_stats_content($csv = FALSE, $page = 0, $all = FALSE) {
  $delta = 'islandora_collection_stats';
  $subject = 'Islandora Collections';
  $headings = array('date' => 'Date',
                    'count' => 'Count',
                    'PID' => 'PID',
                    'model_desc' => 'Model');
  $sql = 'SELECT i.date, i.count, i.PID, m.model_desc ' .
         'FROM {islandora_stats_collection_models} i ' .
         'JOIN {islandora_stats_models} m ON (m.model_id = i.model_id) ' .
         'WHERE m.model_desc = \'Book\' ' . 
         'ORDER BY i.date, i.PID, m.model_desc';
  return _get_SQL_report($delta, $subject, $sql, $headings, $csv, $page, $all, '');
}

function upitt_dashboard_orphanManuscript_getcount($csv = FALSE, $page = 0, $all = FALSE) {
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:bookCModel*)';
  return _get_numFound($q, "");
}

function upitt_dashboard_orphanManuscript_content($csv = FALSE, $page = 0, $all = FALSE) {
  $delta = 'orphanManuscript';
  $subject = 'Orphan manuscript ("Book")';
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:bookCModel*)';
  $fq = "";
  $fl = "PID,RELS_EXT_hasModel_uri_ms,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_hasModel_uri_ms' => 'Model/s',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites');
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all);
}

function upitt_dashboard_orphanImages_getcount($csv = FALSE, $page = 0, $all = FALSE) {
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:sp_large_image_cmodel*)';
  return _get_numFound($q, "");
}

function upitt_dashboard_orphanImages_content($csv = FALSE, $page = 0, $all = FALSE) {
  $delta = 'orphanImages';
  $subject = 'Orphan Images (sp_large_image_cmodel)';
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:sp_large_image_cmodel*)';
  $fq = "";
  $fl = "PID,RELS_EXT_hasModel_uri_ms,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_hasModel_uri_ms' => 'Model/s',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites');
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all);
}

/**
 * This returns the block-themed $subject, $content based on the report
 * parameters.  This is called by the upitt_dashboard_block_view code by a
 * dynamically created function name that corresponds to the block delta like
 * upitt_dashboard_{BLOCK_DELTA}_content.
 *
 * @param type $delta - block identifier.
 * @param type $subject - Title of the block
 * @param type $sql - the SQL statement behind the report
 * @param type $headings - array of SOLR fieldnames and the titles for those
 *               to use for the table output.
 * @param type $csv - TRUE / FALSE - whether or not the output should be CSV.
 * @param type $page - which page of the data the report is pulling, uses
 *               CST_ITEMS_PER_PAGE to calculate solr "start" value
 * @param type $alternate_db - connection string containing host, username, password, and database for alternate database connection
 *               in the format of u=USERNAME,p=PASSWORD,h=HOST,db=DBNAME
 * @return type array of themed block content and the block subject
 */
function _get_SQL_report($delta, $subject, $sql, $headings, $csv, $page, $all, $alternate_db) {
  //  error_log('in _get_SQL_report(' . $delta . ', ' . $subject . ', ' . $sql . ', '.  print_r($headings, true). ', csv, ' . $page . ',  ' . $all . ')');
  if ($alternate_db) {
    $db_conn_params = explode(",", $alternate_db);
    $vals = array();
    foreach ($db_conn_params as $db_conn_param) {
      @list($n, $v) = explode("=", $db_conn_param);
      $vals[$n] = $v;
    }
    if (!array_key_exists('h', $vals) || !array_key_exists('u', $vals) || !array_key_exists('p', $vals) || !array_key_exists('db', $vals)) {
      drupal_set_message('database connection not correct for ' . $delta . ' report');
      return false;
    }
    $link = mysql_connect($vals['h'], $vals['u'], $vals['p']);
    if (!$link) {
      die('Could not connect: ' . mysql_error());
    }
    mysql_select_db($vals['db'], $link);
  }

  $start = $_REQUEST['page'] * CST_ITEMS_PER_PAGE;
  @list($remove_select, $remaining_sql) = explode(" FROM ", $sql);
  $count_query = "SELECT COUNT(*) AS total FROM " . $remaining_sql;
  $count_result = ($alternate_db) ? mysql_fetch_row(mysql_query($count_query)) : db_query($count_query);
  $total = $count_result->fetchObject();
  $num_found = $total->total;

//  $query_items = db_query_range($sql,$start,CST_ITEMS_PER_PAGE);
//  $items = $query_items->fetchAll();

  $sql .= ' LIMIT ' . (($start) ? $start . ', ' : '')  . CST_ITEMS_PER_PAGE;
  $items = ($alternate_db) ? _mysql_query_fetchAll($sql, $link) : db_query($sql)->fetchAll();

  $results = array();
  foreach ($items as $obj) {
    $arr = (array) $obj;
    if (isset($arr['PID'])) {
      $arr['PID'] = l($arr['PID'], '/islandora/object/' . $arr['PID']);
    }
    $results[] = $arr;
  } 

  $search_link = ""; //l(t('Results as Search'), '/islandora/search?islandora_solr_search_navigation=0&f[0]=' . $q . '&f[1]=' . $fq);
  $view_all = ($all || $num_found < CST_ITEMS_PER_PAGE) ? '' : l(t('View all'), 'upitt_dashboard/report_block/' . $delta . '/all');
  if (!$csv) {
    $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/' . $delta . '/downloadcsv');
    $table = theme('table', array('header' => $headings, 'rows' => $results));
    $content = theme('data_table_wrapper',
      array('download_csv' => $download_csv,
            'search_link' => $search_link,
            'view_all' => $view_all,
            'num_found' => $num_found,
            'table' => $table));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    @unlink($filename);
  }
  if ($alternate_db) {
    mysql_close($link);
  }
  return array($subject, $content, $num_found);
}

/**
 * This returns the block-themed $subject, $content based on the report
 * parameters.  This is called by the upitt_dashboard_block_view code by a
 * dynamically created function name that corresponds to the block delta like
 * upitt_dashboard_{BLOCK_DELTA}_content.
 *
 * @param type $delta - block identifier.
 * @param type $subject - Title of the block
 * @param type $q - SOLR q "query" part of the query
 * @param type $fq - SOLR fq "filter query" part of the query
 * @param type $fl - SOLR fl "field list" part of the query
 * @param type $headings - array of SOLR fieldnames and the titles for those
 *               to use for the table output.
 * @param type $csv - TRUE / FALSE - whether or not the output should be CSV.
 * @param type $page - which page of the data the report is pulling, uses
 *               CST_ITEMS_PER_PAGE to calculate solr "start" value
 * @return type array of themed block content and the block subject
 */
function _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page, $all) {
  $num_found = _get_numFound($q, $fq);
  module_load_include('inc', 'islandora_solr', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = $q;

  $start = $_REQUEST['page'] * CST_ITEMS_PER_PAGE;

  $query_processor->solrStart = ($all | $csv) ? 5000 * $page : CST_ITEMS_PER_PAGE * $page;
  $query_processor->solrLimit = ($all | $csv) ? 5000 : CST_ITEMS_PER_PAGE;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $results = array();
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    if ($tmp['response']['numFound'] > 0) {
      foreach ($tmp['response']['docs'] as $rec) {
        if (isset($rec['PID']) && isset($rec['fgs_label_s']) && !$csv) {
          $rec['PID'] = l($rec['PID'], '/islandora/object/' . $rec['PID']);
        }

        foreach ($rec as $key=>$val) {
          if (is_array($rec[$key])) {
            $rec[$key] = implode(" | ", $rec[$key]);
          }
        }
        $results[] = $rec;
      }
    }
  }
  catch (Exception $e) {
  }

  $search_link = ""; //l(t('Results as Search'), '/islandora/search?islandora_solr_search_navigation=0&f[0]=' . $q . '&f[1]=' . $fq);
  $view_all = ($all || $num_found < CST_ITEMS_PER_PAGE) ? '' : l(t('View all'), 'upitt_dashboard/report_block/' . $delta . '/all');
  $heading_fields = array_keys($headings);
  $merge_fieldnames = array();
  foreach ($heading_fields as $heading_field) {
    $merge_fieldnames[$heading_field] = '';
  }
  foreach ($results as $i => $result) {
    $results[$i] = array_merge($merge_fieldnames, $result);
  }
  if (!$csv) {
    $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/' . $delta . '/downloadcsv');
    $table = theme('table', array('header' => $headings, 'rows' => $results));
    $content = theme('data_table_wrapper', 
      array('download_csv' => $download_csv, 
            'search_link' => $search_link, 
            'view_all' => $view_all,
            'num_found' => $num_found, 
            'table' => $table));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    @unlink($filename);
  }
  return array($subject, $content, $num_found);
}

function _get_numFound($q, $fq) {
  module_load_include('inc', 'islandora_solr', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 0;
  $query_processor->solrParams = array(
    'fl' => '',
    'fq' => $fq,
  );
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $num_found = 0;
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    $num_found = $tmp['response']['numFound'];
  }
  catch (Exception $e) {
  }
  return $num_found;
}

function _mysql_query_fetchAll($sql, $link) {
  $result = mysql_query($sql);
  if (!$result) {
    $message  = 'Invalid query: ' . mysql_error() . "\n";
    $message .= 'Whole query: ' . $sql;
    die($message);
  }
  while ($row = mysql_fetch_assoc($result)) {
    if (count($headings) < 1) {
      $headings = array_keys($row);
    }
    if (array_key_exists('do_id', $row)) {
      $pid = 'pitt:' . $row['do_id'];

      if ($obj = islandora_object_load($pid)) {
        $row['do_id'] = l($row['do_id'], '/islandora/object/' . $pid, array('attributes' => array('target' => '_blank')));
      }
    }
    $rows[] = $row;
  }  
}
