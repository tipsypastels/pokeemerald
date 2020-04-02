Quest_GotQuest::
  compare VAR_RESULT, 1
  goto_if_eq Quest_GotQuestSuccessfully
  end

Quest_GotQuestSuccessfully:
  msgbox Quest_GotQuestText, MSGBOX_DEFAULT
  closemessage
  end

Quest_GotQuestText:
  .string "STARTED: {STR_VAR_1}!\n"
  .string "{STR_VAR_2}.$"

Quest_AdvanceQuest::
  compare VAR_RESULT, 2
  goto_if_eq Quest_CompleteQuest
  msgbox Quest_AdvanceQuestText, MSGBOX_DEFAULT
  closemessage
  end

Quest_AdvanceQuestText:
  .string "UPADTED: {STR_VAR_1}!\n"
  .string "{STR_VAR_2}.$"

Quest_CompleteQuest::
  msgbox Quest_CompleteQuestText, MSGBOX_DEFAULT
  closemessage
  end

Quest_CompleteQuestText:
  .string "COMPLETED: {STR_VAR_1}!$"