jQuery(document).ready( function() {
	jQuery('#block-views-prizes-block, #block-views-leaderboard-block').addClass('well');

	jQuery('#message-all-form').before('<div id="moveLicensesHere"></div>');
	jQuery('#manage-licenses-button').appendTo('#moveLicensesHere')
		.before('<button type="button" id="manageLicensesBtn" class="btn">Manage Licenses</button>');
	jQuery('#edit-licenses-checkbox').parents('label').hide();
	jQuery('#manageLicensesBtn').click( function() {
		jQuery('#edit-licenses').toggle();
	});

	jQuery('#message-all-form').before('<button type="button" id="messageAllBtn" class="btn">Message All Players</button>');
	jQuery('#edit-message-checkbox').parents('label').hide();
	jQuery('#messageAllBtn').click( function() {
		jQuery('#edit-message').toggle();
	});

});