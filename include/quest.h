#ifndef GUARD_QUEST_H
#define GUARD_QUEST_H

struct QuestStep {
  /**
   * Name of the step.
   */
  const u8 *name;
  /**
   * Location of the quest destination, which will be shown to the player. Can be 0 for unset.
   */
  const u16 mapId;
};

struct Quest {
  /**
   * Name of the quest as an array of characters.
   */
  const u8 *name;
  /**
   * The ID of the flag to set when the quest is begun and set off when it completes.
   */
  const u16 ongoingFlag;
  /**
   * The ID of the flag to set when the quest is complete.
   */
  const u16 completedFlag;
  /**
   * The ID of the variable that tracks the current state of the quest. Must be present and match up with the current index in the quest steps list.
   */
  const u16 progressVar;
  /**
   * The index of the first step in the steps list.
   */
  const u16 firstStepIdx;
  /**
   * The index of the last step in the steps list.
   */
  const u16 lastStepIdx;
};

bool8 GiveQuest(u16);
bool8 GiveQuestSilent(u16);
bool8 HasQuest(u16);
bool8 DidCompleteQuest(u16);
bool8 HasOrCompletedQuest(u16);
u16 GetCurrentQuestStepId(u16);
void ResetQuest(u16);
void AdvanceQuest(u16);
void CompleteQuest(u16);
void SetQuestStep(u16, u16);

#endif