Quest_GotQuest::
  compare VAR_RESULT, 1
  goto_if_eq Quest_GotQuestSuccessfully
  end

Quest_GotQuestSuccessfully:
  msgbox Quest_GotQuestText, MSGBOX_DEFAULT
  closemessage
  end

Quest_GotQuestText:
  .string "Quest began: {STR_VAR_1}!$"