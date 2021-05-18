from abc import ABC, abstractmethod
from copy import deepcopy


class SchedulerBase(ABC):  # abstract class

    def __init__(self):
        self.hyper_parameters = dict()

    def __call__(self, step=None):
        return self.learning_rate(step=step)

    def copy(self):
        return deepcopy(self)  # deep copy

    def set_params(self, hyper_param_dict):
        if hyper_param_dict is not None:
            for k, v in hyper_param_dict.items():
                if k in self.hyper_parameters:
                    self.hyper_parameters[k] = v

    @abstractmethod
    def learning_rate(self, step):
        raise NotImplementedError
