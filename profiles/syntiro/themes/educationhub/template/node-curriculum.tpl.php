<?php
// $Id: node-curriculum.tpl.php,v 1.4.2.1 2009/08/10 10:48:33 goba Exp $

/**
 * @file node-curriculum.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 *
 * Node status variables:
 * - $page: Flag for the full page state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $commentform: Add new comments form of the node.
 *
 * @see assignment_preprocess_node()
 */
?>
<?php if($preview_line): ?>
<div class="curriculum-preview" style="display:none">
  <div class="common-list-drop-preview" style="display:none">
    <a title="results" class=""  href="#">Preview</a>
  </div>
</div>
<?php endif; ?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky';} ?><?php if (!$status) { print ' ';} ?> node-preview clearfix<?php if(!$preview_line){print ' no-preview';}?>">
  <?php if ($page == 0) { ?>
    <div class='teaser-view'>
      <div class="result-right">
        <div class="result-right-inner clearfix">
          <div>
            <h3>
              <?php print $title; ?>
            </h3>
          </div>
          <?php if ($name): ?>
            <div class="author-name">
              <span>
                <?php print $name; ?>
              </span> |
              <span class="node-relate-type">
              <?php print $type; ?>
              </span>
            </div>
          <?php endif; ?>
        </div>
        <div class="content">
          <?php print strip_tags($content); ?>
        </div>
        <div class="discussion-comments">
          <ul class="clearfix">
            <li class="last"> <?php print $comment_count; ?></li>
          </ul>
        </div>
      </div>
    </div>
  <?php } ?>
  <?php if ($page == 1) { ?>
  <!-- The below tag has been commented for accessibility-->
   <!-- <h2 class="titlespace" style="display:none"></h2> -->
    <?php if ($edit_tip) { ?> <div class="tip-description" ><?php print $edit_tip; ?></div> <?php } ?>
    <div class='curriculum-desc'>

      <span title="<?php print $edit_title; ?>" class="<?php if ($playlist_description_class){ print $playlist_description_class; } ?>">
      <?php print $description; ?>
      </span>
    </div>
    <div class="clearfix curriculum-overall">
      <div class="float-left curriculum-left">
        <ul>
          <li> <?php print $select_all; ?></li>
          <li class="sel-all"> <?php print $popup_selectall; ?></li>

          <!-- Assign icons -->
          <li class="assign-active" style="display:none"> <?php print $assign; ?></li>
          <li class="assign-inactive"> <?php print $assign_disable; ?></li>
          <li class="assign-form-active" style="display:none"> <?php print $assign_form_active; ?></li>
          <li class="assign-unpublished" style="display:none"> <?php print $assign_unpublished; ?></li>

          <!-- Delete icons -->
          <li class="delete-active" style="display:none"> <?php print $delete; ?></li>
          <li class="delete-disable"> <?php print $delete_disable; ?></li>
          <li class="delete-form-active" style="display:none"> <?php print $delete_form_active; ?></li>
          
          <!-- Save Reorder icons -->
          <li class="delete-active" style="display:none"> <?php print $savereorder; ?></li>
          <li class="delete-disable"> <?php print $savereorder_disable; ?></li>
          <li class="delete-form-active" style="display:none"> <?php print $savereorder_form_active; ?></li>


        </ul>
      </div>
      <div class="float-right curriculum-right">
        <ul>
          <li class="topic-active"> <?php print $add_topic; ?></li>
          <li class="topic-inactive" style="display:none"> <?php print $add_topic_disable; ?></li>
        </ul>
      </div>
    </div>
    <?php if($assignment_form): ?>
    <div class="curriculum-assignment-form" style="display:none">
      <span class="assign-heading"><?php print $assignment_heading; ?></span>
      <?php print $assignment_form; ?>
    </div>
    <?php endif; ?>
    <?php if ($edit_description_icon) { ?>
      <div class="clearfix">
        <div class="node-preview-left">
          <div class="curriculum-topic">
            <?php if ($no_topic) { ?>
              <div class="result node-empty-content"><p><?php print $no_topic; ?></p></div>
            <?php } else { ?>
              <?php if(count($fields) > 0) { ?>
                <?php foreach ($fields as $key => $value) { ?>
                  <div class="topics "  id="topic_<?php print $value['topic_id']; ?>"  topic_id="<?php print $value['topic_id']; ?>"  order_weight="<?php print $value['weight']; ?>" >

                    <div class="common-list-wrapper">
                    <!--  <span class="handle">-->
                      <div class="common-list-drop topic-title-inline">

                        <div class="topic-left"><span class="topic-inline-edit2" title="Click To Edit"><?php print $value['topic_title']; ?></span><?php if ($value['edit_topic_link']) { ?>
                            <span>
                              <?php print $value['edit_topic_link'] ?>
                            </span>
                          <?php } ?></div>
                        <span class="open-close-topics-playlist"> <a href="javascript:;"><span class="open-close-title-expand"></span></a><?php //print $list_drop; ?> </span><span><?php print $value['delete_topic_link']; ?></span>
                    </div>
                      <div class="clearfix topics-top-content">
                        <div class="topic-left">
                        </div>
                      <div class="topic-right">
                          <span title="Move This Up" class="topic-handle topic-handle-up">
                          </span>
                          <span title="Move This Down" class="topic-handle topic-handle-down">
                          </span>
                      </div>
                    </div>
                    <?php if($value['topic_unavailable']) { ?>
                      <div class="empty-subtopic ui-droppable"><?php print $value['topic_unavailable']; ?></div>
                    <?php } ?>
                    <div id="content_<?php print $value['topic_id']; ?>" topic_id="<?php print $value['topic_id']; ?>" class="topic_content" style="min-height:50px;">

                      <?php if ($value['subfield']) { ?>
                        <?php foreach ($value['subfield'] as $subkey => $subvalue) { ?>
                          <div class="clearfix assign-edit-icons topic-single-content" id="content_<?php print $subvalue['curriculum_id']; ?>">
                            <div class="float-left sub-topics">
                                <?php print $subvalue['check_box']; ?>
                            </div>
                            
                              <div class="sub-topics playlist-action">
                              <div class="more-icon">
                                <?php print $subvalue['more_icon']; ?>
                              </div>
                             <!-- <div class="playlist-topic"> -->
                                <?php //print $subvalue['select_topic']; ?>
                             <!-- </div> -->

                            <!-- <div class="playlist-weight"> -->
                                <?php //print $subvalue['weight']; ?>
                               <!-- </div> -->
                            </div>
                            
                            <?php if ($subvalue['assigned_members']) { ?>
                            <div class="float-left sub-topics">
                                <?php print $subvalue['assigned_members']; ?>
                            </div>
                            <?php } ?>
                            <!-- Handle for subtopics-->
<!--                            <div class="sub-topics-drag">fdsf</div>
-->                            <div class="float-left  sub-topics"  content_title="<?php print $subvalue['content_title']; ?>" class_type="<?php print $subvalue['type']; ?>"  content_type="<?php print $subvalue['type']; ?>" content_asset="<?php print $subvalue['body']; ?>">
                            <span class="handle">
                                <div class="asset-teaser"><?php print $subvalue['asset_title'];?></div><p><?php print $subvalue['body']; ?></p>
                                </span>
                            </div>
                            <?php //if($subvalue['delete_content_link']) { ?>
                              <?php //print $subvalue['delete_content_link']; ?>
                            <?php //} ?>
                          </div>
                        <?php }  ?>
                      <?php } ?>

                    </div>
                    <!--</span>  -->
                  </div>

                </div>
              <?php } ?>
            <?php } ?>
          <?php } ?>
        </div>
      </div>
    </div>
  <?php } else { ?>
    <?php if ($no_topic) { ?>
      <div class="result node-empty-content"><p><?php print $no_topic; ?></p></div>
    <?php } else { ?>

      <div class="clearfix">
        <div class="node-preview-left">
          <?php if(count($fields) > 0){ ?>
            <div class="curriculum-topic">
            <?php foreach ($fields as $key => $value) {?>
              <div class="topics">
                <div id="topic_<?php print $value['topic_id']; ?>" class="clearfix topics-top-content">
                  <div class="common-list-wrapper">
                    <div class="common-list-drop topic-title-inline"><span><?php print $value['topic_title']; ?></span><span class=""> <?php print $list_drop; ?> </span><span><?php print $close_image; ?></span>
                    </div>
                    <div id="content_<?php print $value['topic_id']; ?>" topic_id="<?php print $value['topic_id']; ?>" class=" topic-content-view" style="min-height:50px;">
                    <?php if ($value['subfield']) {  ?>
                      <?php foreach ($value['subfield'] as $subkey => $subvalue) {  ?>
                        <div class="clearfix assign-view-icons assign-edit-icons topic-single-content  " >
                        <div class="float-left sub-topics">
                                <?php print $subvalue['check_box']; ?>
                            </div>
                          <div class="float-left sub-topics">
                            <div class="more-icon">
                              <?php print $subvalue['more_icon']; ?>
                            </div>
                          </div>

                          <?php if ($subvalue['assigned_members']) { ?>
                            <div class="float-left sub-topics">
                                <?php print $subvalue['assigned_members']; ?>
                            </div>
                            <?php } ?>
                          <span class="handles">
                            <div class="asset-teaser"><?php print $subvalue['asset_title']; ?></div><p><?php print $subvalue['body']; ?></p>
                          </span>
                          <?php if ($access && $subvalue['assign_link']) { ?>
                            <?php print $subvalue['assign_link']; ?>
                          <?php } ?>
                          <?php //if ($access && $subvalue['assignment_link']) { ?>
                            <?php //print $subvalue['assignment_link']; ?>
                          <?php //} ?>
                        </div>
                      <?php } ?>
                    <?php } ?>
                  </div>
                </div>
              </div>
            </div>
          <?php } ?>
          </div>
        <?php } ?>
      </div>
      <!--<div class="node-preview-right"><div class="node-preview-right-content"></div></div>-->
    </div>

  <?php } ?>
 <?php } ?>
<!-- Five Star Ratings  -->
</div>
  <!--Print Adobe Prompt message -->
  <?php if (isset($adobe_message)) {?>
    <?php print $adobe_message; ?>
  <?php } ?>

  <!--Print Actions Buttons -->
  <?php if (isset($actions)) {?>
    <div class="art-actions">
      <div class="clearfix">
        <!-- Five Star Ratings  -->
        <?php if (isset($fivestar_label) && $fivestar_widget){ ?>
          <div class="rating float-left clearfix">
            <span><?php print $fivestar_label; ?></span>
            <?php print $fivestar_widget; ?>
          </div>
        <?php } ?>
        <?php if (isset($actions_options)): ?>
          <div class="action-main float-left">
           <div class="action-main-button">
              <?php if (isset($actions)): ?>
                <?php print $actions; ?>
              <?php endif; ?>
           </div>
           <div class="action-buttons element-invisible" >
              <?php if (isset($actions_options)): ?>
                <?php print $actions_options; ?>
              <?php endif; ?>
           </div>
          </div>
        <?php endif; ?>
        <?php if (isset($view_count)): ?>
          <div class="views-count float-right"><?php print $view_count; ?></div>
        <?php endif; ?>
      </div>
      <?php if (isset($share_form)) { ?>
        <div class="art-actions-block share-form-block" style="display: none">
          <a class="close" title="Close" href="#">Close</a>
          <div class="clearfix">
            <?php print $share_form; ?>
          </div>
        </div>
      <?php } ?>
      <?php if (isset($recommend_form)) { ?>
        <div class="art-actions-block assign-form-block" style="display: none">
          <?php print $recommend_form; ?>
        </div>
      <?php } ?>
    </div>
  <?php } ?>
  <!--Print Comment and Reviews Tab -->
  <?php if($commenttab || $reviewstab): ?>
   <div class="clear-block" id="tabs-wrapper">
    <ul class="comment-review-tabs primary tabs">
      <?php if(isset($commenttab)): ?>
        <li class="comment-tab"><?php print $commenttab; ?></li>
      <?php endif; ?>
      <?php if(isset($reviewstab)): ?>
        <li class="review-tab"><?php print $reviewstab; ?></li>
      <?php endif; ?>
    </ul>
   </div>
  <?php endif; ?>

  <!-- Display Add new comments form for this content type -->
  <?php if (isset($commentform)): ?>
     <?php print $commentform;  ?>
  <?php endif; ?>

  <!-- Display Reviews form for this content type -->
  <?php if (isset($reviewsform)): ?>
   <div class="review-box">
    <div class="content">
     <?php print $reviewsform;  ?>
    </div>
   </div>
  <?php endif; ?>

  <!-- Reviews listing -->
  <?php if($reviews_listing): ?>
    <div id="reviews">
      <div class="reviews-list">
        <?php print $reviews_listing; ?>
      </div>
    </div>
  <?php endif; ?>
<?php } ?>

<?php if ($page == 1) { ?>
  <?php if (!$edit_description_icon) {
    //print $commentform;
  } ?>
<?php } ?>
